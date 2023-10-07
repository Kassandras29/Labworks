#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>

class InfoSize {
public:
    const static int kTEXT_ENCODING = 1;
    const static int kRATING = 1;
    const static int kBYTE = 1;
    const static int kTIME_STAMP_FORMAT = 1;
    const static int kCONTENT_TYPE = 1;
    const static int kFRAME_FLAGS = 2;
    const static int kFREQUENCY = 2;
    const static int kVOLUME_ADJUSTMENT = 2;
    const static int kFILE_IDENTIFIER = 3;
    const static int kLANGUAGE = 3;
    const static int kBUFFER = 3;
    const static int kSIZE_FRAMES = 4;
    const static int kNAME_FRAME = 4;
    const static int kDATE = 8;
    const static int kSIZE_HEADER = 10;
    const static int kTWO_IN_THE_SEVENTH = 128;
};

class Frame {
public:
    std::string frame_name_;
    uint32_t frame_size_;

    Frame(std::string& frame_name, uint32_t frame_size);
    virtual ~Frame() = 0;

    virtual void PrintInfo() {};

};

class TextFrame : public Frame {
public:
    char text_encoding_;
    std::vector<std::string> information_;

    TextFrame(std::string& frame_name, uint32_t frame_size);

    void PrintInfo() override;

};

class URLFrame : public Frame {
public:
    std::string link_;

    URLFrame(std::string& frame_name, uint32_t frame_size);

    void PrintInfo() override;

};

class TXXX : public TextFrame {
public:
    std::string description_;

    TXXX(std::string& frame_name, uint32_t frame_size);

    void PrintInfo() override;

};

class WXXX : public URLFrame {
public:
    char text_encoding_;
    std::string description_;

    WXXX(std::string& frame_name, uint32_t frame_size);

    void PrintInfo() override;

};

class USER : public TextFrame {
public:
    std::string language_;

    USER(std::string& frame_name, uint32_t frame_size);

    void PrintInfo() override;

};

class COMM : public USER {
public:
    std::string short_description_;

    COMM(std::string& frame_name, uint32_t frame_size);

    void PrintInfo() override;

};

class USLT : public USER {
public:
    std::string content_description_;

    USLT(std::string& frame_name, uint32_t frame_size);

    void PrintInfo() override;

};

class PCNT : public Frame {
public:
    uint64_t counter_;

    PCNT(std::string& frame_name, uint32_t frame_size);

    void PrintInfo() override;

};

class POPM : public PCNT {
public:
    std::string email_to_user_;
    int rating_;

    POPM(std::string& frame_name, uint32_t frame_size);

    void PrintInfo() override;

};

class UFID : public URLFrame {
public:
    std::string identifier_;

    UFID(std::string& frame_name, uint32_t frame_size);

    void PrintInfo() override;

};

class PRIV : public URLFrame {
public:
    std::string identifier_;

    PRIV(std::string& frame_name, uint32_t frame_size);

    void PrintInfo() override;

};

class LINK : public UFID {
public:
    std::vector<std::string> additional_data_;

    LINK(std::string& frame_name, uint32_t frame_size);

    void PrintInfo() override;

};

class SEEK : public Frame {
public:
    uint32_t offset_next_tag_;

    SEEK(std::string& frame_name, uint32_t frame_size);

    void PrintInfo() override;

};

class RBUF : public SEEK {
public:
    uint32_t buffer_size_;
    char flag_;

    RBUF(std::string& frame_name, uint32_t frame_size);

    void PrintInfo() override;

};

class EQU2 : public Frame {
public:
    char interpolation_method_;
    std::string identification_;
    uint32_t frequency_;
    uint32_t volume_adjustment_;

    EQU2(std::string& frame_name, uint32_t frame_size);

    void PrintInfo() override;

};

class RVA2 : public Frame {
public:
    std::string identification_;
    char type_channel_;
    uint32_t volume_adjustment_;
    char bits_representing_peak_;
    std::string peak_volume_;

    RVA2(std::string& frame_name, uint32_t frame_size);

    void PrintInfo() override;

};

class POSS : public Frame {
public:
    char time_stamp_format_;
    uint32_t time_stamp_;

    POSS(std::string& frame_name, uint32_t frame_size);

    void PrintInfo() override;

};

class ETCO : public POSS {
public:
    char type_event_;

    ETCO(std::string& frame_name, uint32_t frame_size);

    void PrintInfo() override;

};

class SYLT : public USLT {
public:
    char time_stamp_format_;
    char content_type_;
    std::string sync_identifier_;
    uint32_t time_stamp_;

    SYLT(std::string& frame_name, uint32_t frame_size);

    void PrintInfo() override;

};

class OWNE : public TextFrame {
public:
    std::string price_;
    std::string date_;
    std::string seller_;

    OWNE(std::string& frame_name, uint32_t frame_size);

    void PrintInfo() override;

};

class COMR : public OWNE {
public:
    std::string contact_URL_;
    char received_as_;
    std::string description_;
    std::string picture_MIME_type_;
    std::string seller_logo_;

    COMR(std::string& frame_name, uint32_t frame_size);

    void PrintInfo() override;

};

class ENCR : public Frame {
public:
    std::string owner_identifier_;
    char method_symbol_;
    std::string encryption_data_;

    ENCR(std::string& frame_name, uint32_t frame_size);

    void PrintInfo() override;

};

class GRID : public Frame {
public:
    std::string owner_identifier_;
    char symbol_group_;
    std::string group_dependent_data_;

    GRID(std::string& frame_name, uint32_t frame_size);

    void PrintInfo() override;

};

std::vector<std::shared_ptr<Frame>> Parse(std::ifstream& is, uint32_t size_frames_bytes,
                                          std::vector<std::shared_ptr<Frame>> Frames);
