#include "frame.h"
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <cmath>

Frame::Frame(std::string& frame_name, uint32_t frame_size)  {
    frame_name_ = std::move(frame_name);
    frame_size_ = frame_size;
}

TextFrame::TextFrame(std::string& frame_name, uint32_t frame_size) : Frame(frame_name, frame_size) {}

void TextFrame::PrintInfo() {

    std::cout << '\n' << "Frame`s name: " << frame_name_ << '\n';
    std::cout << "Frame`s size: " << frame_size_ << '\n';

    for (const auto& info : information_) {
        std::cout << info << '\n';
    }
}

URLFrame::URLFrame(std::string& frame_name, uint32_t frame_size) : Frame(frame_name, frame_size) {}

void URLFrame::PrintInfo() {

    std::cout << '\n' << "Frame`s name: " << frame_name_ << '\n';
    std::cout << "Frame`s size: " << frame_size_ << '\n';
    std::cout << link_ << '\n';
}

TXXX::TXXX(std::string& frame_name, uint32_t frame_size) : TextFrame(frame_name, frame_size) {}

void TXXX::PrintInfo() {

    std::cout << '\n' << "Frame`s name: " << frame_name_ << '\n';
    std::cout << "Frame`s size: " << frame_size_ << '\n';
    std::cout << description_ << '\n';

    for (const auto& info : information_) {
        std::cout << info << '\n';
    }
}

WXXX::WXXX(std::string& frame_name, uint32_t frame_size) : URLFrame(frame_name, frame_size) {}

void WXXX::PrintInfo() {

    std::cout << '\n' << "Frame`s name: " << frame_name_ << '\n';
    std::cout << "Frame`s size: " << frame_size_ << '\n';
    std::cout << description_ << '\n';
    std::cout << link_ << '\n';
}

USER::USER(std::string& frame_name, uint32_t frame_size) : TextFrame(frame_name, frame_size) {}

void USER::PrintInfo() {

    std::cout << '\n' << "Frame`s name: " << frame_name_ << '\n';
    std::cout << "Frame`s size: " << frame_size_ << '\n';
    std::cout << "Language: " << language_ << '\n';

    for (const auto& info : information_) {
        std::cout << info << '\n';
    }
}

COMM::COMM(std::string& frame_name, uint32_t frame_size) : USER(frame_name, frame_size) {}

void COMM::PrintInfo() {

    std::cout << '\n' << "Frame`s name: " << frame_name_ << '\n';
    std::cout << "Frame`s size: " << frame_size_ << '\n';
    std::cout << "Language: " << language_ << '\n';
    std::cout << short_description_ << '\n';

    for (const auto& info : information_) {
        std::cout << info << '\n';
    }
}

USLT::USLT(std::string& frame_name, uint32_t frame_size) : USER(frame_name, frame_size) {}

void USLT::PrintInfo() {

    std::cout << '\n' << "Frame`s name: " << frame_name_ << '\n';
    std::cout << "Frame`s size: " << frame_size_ << '\n';
    std::cout << "Language: " << language_ << '\n';
    std::cout << content_description_ << '\n';

    for (const auto& info : information_) {
        std::cout << info << '\n';
    }
}

PCNT::PCNT(std::string& frame_name, uint32_t frame_size) : Frame(frame_name, frame_size) {}

void PCNT::PrintInfo() {

    std::cout << '\n' << "Frame`s name: " << frame_name_ << '\n';
    std::cout << "Frame`s size: " << frame_size_ << '\n';
    std::cout << counter_ << '\n';
}

POPM::POPM(std::string& frame_name, uint32_t frame_size) : PCNT(frame_name, frame_size) {}

void POPM::PrintInfo() {

    std::cout << '\n' << "Frame`s name: " << frame_name_ << '\n';
    std::cout << "Frame`s size: " << frame_size_ << '\n';
    std::cout << email_to_user_ << '\n';
    std::cout << rating_ << '\n';
    std::cout << counter_ << '\n';
}

UFID::UFID(std::string& frame_name, uint32_t frame_size) : URLFrame(frame_name, frame_size) {}

void UFID::PrintInfo() {

    std::cout << '\n' << "Frame`s name: " << frame_name_ << '\n';
    std::cout << "Frame`s size: " << frame_size_ << '\n';
    std::cout << link_ << '\n';
    std::cout << identifier_ << '\n';
}

PRIV::PRIV(std::string& frame_name, uint32_t frame_size) : URLFrame(frame_name, frame_size) {}

void PRIV::PrintInfo() {

    std::cout << '\n' << "Frame`s name: " << frame_name_ << '\n';
    std::cout << "Frame`s size: " << frame_size_ << '\n';
    std::cout << link_ << '\n';
    std::cout << identifier_ << '\n';
}

LINK::LINK(std::string& frame_name, uint32_t frame_size) : UFID(frame_name, frame_size) {}

void LINK::PrintInfo() {

    std::cout << '\n' << "Frame`s name: " << frame_name_ << '\n';
    std::cout << "Frame`s size: " << frame_size_ << '\n';
    std::cout << identifier_ << '\n';
    std::cout << link_ << '\n';

    for (const auto& info : additional_data_) {
        std::cout << info << '\n';
    }
}

SEEK::SEEK(std::string& frame_name, uint32_t frame_size) : Frame(frame_name, frame_size) {}

void SEEK::PrintInfo() {

    std::cout << '\n' << "Frame`s name: " << frame_name_ << '\n';
    std::cout << "Frame`s size: " << frame_size_ << '\n';
    std::cout << offset_next_tag_ << '\n';
}

RBUF::RBUF(std::string& frame_name, uint32_t frame_size) : SEEK(frame_name, frame_size) {}

void RBUF::PrintInfo() {

    std::cout << '\n' << "Frame`s name: " << frame_name_ << '\n';
    std::cout << "Frame`s size: " << frame_size_ << '\n';
    std::cout << buffer_size_ << '\n';
    std::cout << offset_next_tag_ << '\n';
}

EQU2::EQU2(std::string& frame_name, uint32_t frame_size) : Frame(frame_name, frame_size) {}

void EQU2::PrintInfo() {

    std::cout << '\n' << "Frame`s name: " << frame_name_ << '\n';
    std::cout << "Frame`s size: " << frame_size_ << '\n';
    std::cout << identification_ << '\n';
    std::cout << frequency_ << '\n';
    std::cout << volume_adjustment_ << '\n';
}

RVA2::RVA2(std::string& frame_name, uint32_t frame_size) : Frame(frame_name, frame_size) {}

void RVA2::PrintInfo() {

    std::cout << '\n' << "Frame`s name: " << frame_name_ << '\n';
    std::cout << "Frame`s size: " << frame_size_ << '\n';
    std::cout << identification_ << '\n';
    std::cout << volume_adjustment_ << '\n';
    std::cout << peak_volume_ << '\n';
}

POSS::POSS(std::string& frame_name, uint32_t frame_size) : Frame(frame_name, frame_size) {}

void POSS::PrintInfo() {

    std::cout << '\n' << "Frame`s name: " << frame_name_ << '\n';
    std::cout << "Frame`s size: " << frame_size_ << '\n';
    std::cout << time_stamp_ << '\n';
}

ETCO::ETCO(std::string& frame_name, uint32_t frame_size) : POSS(frame_name, frame_size) {}

void ETCO::PrintInfo() {

    std::cout << '\n' << "Frame`s name: " << frame_name_ << '\n';
    std::cout << "Frame`s size: " << frame_size_ << '\n';
    std::cout << time_stamp_ << '\n';
}

SYLT::SYLT(std::string& frame_name, uint32_t frame_size) : USLT(frame_name, frame_size) {}

void SYLT::PrintInfo() {

    std::cout << '\n' << "Frame`s name: " << frame_name_ << '\n';
    std::cout << "Frame`s size: " << frame_size_ << '\n';
    std::cout << "Language: " << language_ << '\n';
    std::cout << content_description_ << '\n';
    std::cout << sync_identifier_ << '\n';
    std::cout << time_stamp_ << '\n';
}

OWNE::OWNE(std::string& frame_name, uint32_t frame_size) : TextFrame(frame_name, frame_size) {}

void OWNE::PrintInfo() {

    std::cout << '\n' << "Frame`s name: " << frame_name_ << '\n';
    std::cout << "Frame`s size: " << frame_size_ << '\n';
    std::cout << price_ << '\n';
    std::cout << date_ << '\n';
    std::cout << seller_ << '\n';
}

COMR::COMR(std::string& frame_name, uint32_t frame_size) : OWNE(frame_name, frame_size) {}

void COMR::PrintInfo() {

    std::cout << '\n' << "Frame`s name: " << frame_name_ << '\n';
    std::cout << "Frame`s size: " << frame_size_ << '\n';
    std::cout << price_ << '\n';
    std::cout << date_ << '\n';
    std::cout << contact_URL_ << '\n';
    std::cout << seller_ << '\n';
    std::cout << description_ << '\n';
    std::cout << picture_MIME_type_ << '\n';
    std::cout << seller_logo_ << '\n';
}

ENCR::ENCR(std::string& frame_name, uint32_t frame_size) : Frame(frame_name, frame_size) {}

void ENCR::PrintInfo() {

    std::cout << '\n' << "Frame`s name: " << frame_name_ << '\n';
    std::cout << "Frame`s size: " << frame_size_ << '\n';
    std::cout << owner_identifier_ << '\n';
    std::cout << method_symbol_ << '\n';
    std::cout << encryption_data_ << '\n';
}

GRID::GRID(std::string& frame_name, uint32_t frame_size) : Frame(frame_name, frame_size) {}

void GRID::PrintInfo() {

    std::cout << '\n' << "Frame`s name: " << frame_name_ << '\n';
    std::cout << "Frame`s size: " << frame_size_ << '\n';
    std::cout << owner_identifier_ << '\n';
    std::cout << symbol_group_ << '\n';
    std::cout << group_dependent_data_ << '\n';
}

std::vector<std::shared_ptr<Frame>> Parse(std::ifstream &is, uint32_t size_frames_bytes,
                                          std::vector<std::shared_ptr<Frame>> Frames) {

    while (is.tellg() < size_frames_bytes + InfoSize::kSIZE_HEADER) {

        char *frame_ch = new char [InfoSize::kNAME_FRAME];
        is.read(frame_ch, InfoSize::kNAME_FRAME);

        std::string name_frame;
        for (int i = 0; i < InfoSize::kNAME_FRAME; ++i) {
            name_frame += frame_ch[i];
        }
        delete[] frame_ch;

        char *size_frame_hex = new char [InfoSize::kSIZE_FRAMES];
        is.read(size_frame_hex, InfoSize::kSIZE_FRAMES);

        uint32_t p = InfoSize::kSIZE_FRAMES - 1;
        uint32_t size_frame_bytes = 0;
        for (int i = 0; i < InfoSize::kSIZE_FRAMES; ++i) {
            size_frame_bytes += uint32_t(size_frame_hex[i]) * pow(InfoSize::kTWO_IN_THE_SEVENTH, p);
            --p;
        }
        delete[] size_frame_hex;

        is.seekg(InfoSize::kFRAME_FLAGS, std::ifstream::cur);


        if (name_frame == "AENC" || name_frame == "APIC" || name_frame == "ASPI" || name_frame == "GEOB"
            || name_frame == "MCDI" || name_frame == "MLLT" || name_frame == "RVRB" || name_frame == "SIGN"
            || name_frame == "SYTC" || name_frame == "TFLT" || name_frame == "TMED" || name_frame == "TPRO"
            || name_frame == "TSTU") {

            is.seekg(size_frame_bytes, std::ifstream::cur);

        } else if (name_frame[0] == 'T') {

            if (name_frame == "TXXX") {

                std::shared_ptr<TXXX> frame(new TXXX{name_frame, size_frame_bytes});
                is.read(&frame->text_encoding_, InfoSize::kTEXT_ENCODING);

                std::string part_of_data;
                char byte;
                is.read(&byte, 1);
                int count_bytes = 1;

                while ((int) byte != 0) {
                    part_of_data += byte;
                    is.read(&byte, 1);
                    ++count_bytes;
                }

                frame->description_ = part_of_data;
                part_of_data = "";

                for (int i = count_bytes; i < frame->frame_size_ - InfoSize::kTEXT_ENCODING; ++i) {
                    is.read(&byte, 1);
                    part_of_data += byte;
                }
                frame->information_.push_back(part_of_data);
                part_of_data = "";

                Frames.push_back(frame);

            } else {

                std::shared_ptr<TextFrame> frame (new TextFrame{name_frame, size_frame_bytes});
                is.read(&frame->text_encoding_, InfoSize::kTEXT_ENCODING);

                std::string part_of_data;
                for (int i = 0; i < frame->frame_size_ - InfoSize::kTEXT_ENCODING; ++i) {

                    char byte;
                    is.read(&byte, 1);
                    if ((int) byte == 0) {
                        frame->information_.push_back(part_of_data);
                        part_of_data = "";
                    } else {
                        part_of_data += byte;
                    }
                    if (i == frame->frame_size_ - InfoSize::kTEXT_ENCODING - 1 && (int) byte != 0) {
                        frame->information_.push_back(part_of_data);
                        part_of_data = "";
                    }

                }

                Frames.push_back(frame);
            }

        } else if (name_frame[0] == 'W') {

            if (name_frame == "WXXX") {

                std::shared_ptr<WXXX> frame (new WXXX{name_frame, size_frame_bytes});
                is.read(&frame->text_encoding_, InfoSize::kTEXT_ENCODING);

                std::string part_of_data;
                char byte;
                is.read(&byte, 1);
                int count_bytes = 1;

                while ((int) byte != 0) {
                    part_of_data += byte;
                    is.read(&byte, 1);
                    ++count_bytes;
                }

                frame->description_ = part_of_data;
                part_of_data = "";

                for (int i = count_bytes; i < frame->frame_size_ - InfoSize::kTEXT_ENCODING; ++i) {
                    is.read(&byte, 1);
                    part_of_data += byte;
                }
                frame->link_ = part_of_data;
                part_of_data = "";

                Frames.push_back(frame);

            } else {

                std::shared_ptr<URLFrame> frame (new URLFrame{name_frame, size_frame_bytes});

                for (int i = 0; i < frame->frame_size_; ++i) {
                    char byte;
                    is.read(&byte, 1);
                    frame->link_ += byte;
                }

                Frames.push_back(frame);
            }

        } else if (name_frame == "USER") {

            std::shared_ptr<USER> frame ( new USER{name_frame, size_frame_bytes});
            is.read(&frame->text_encoding_, InfoSize::kTEXT_ENCODING);

            char *language_ch = new char [InfoSize::kLANGUAGE];
            is.read(language_ch, InfoSize::kLANGUAGE);
            std::string language;
            for (int i = 0; i < InfoSize::kLANGUAGE; ++i) {
                language += language_ch[i];
            }
            frame->language_ = language;
            delete[] language_ch;

            std::string part_of_data;
            char byte;

            for (int i = 0; i < frame->frame_size_ - InfoSize::kTEXT_ENCODING - InfoSize::kLANGUAGE; ++i) {
                is.read(&byte, 1);
                part_of_data += byte;
            }
            frame->information_.push_back(part_of_data);
            part_of_data = "";

            Frames.push_back(frame);

        } else if (name_frame == "COMM") {

            std::shared_ptr<COMM> frame ( new COMM{name_frame, size_frame_bytes});
            is.read(&frame->text_encoding_, InfoSize::kTEXT_ENCODING);

            char *language_ch = new char [InfoSize::kLANGUAGE];
            is.read(language_ch, InfoSize::kLANGUAGE);
            std::string language;
            for (int i = 0; i < InfoSize::kLANGUAGE; ++i) {
                language += language_ch[i];
            }
            frame->language_ = language;
            delete[] language_ch;

            std::string part_of_data;
            char byte;
            is.read(&byte, 1);
            int count_bytes = 1;

            while ((int) byte != 0) {
                part_of_data += byte;
                is.read(&byte, 1);
                ++count_bytes;
            }

            frame->short_description_ = part_of_data;
            part_of_data = "";

            for (int i = count_bytes; i < frame->frame_size_ - InfoSize::kTEXT_ENCODING - InfoSize::kLANGUAGE; ++i) {
                is.read(&byte, 1);
                part_of_data += byte;
            }
            frame->information_.push_back(part_of_data);
            part_of_data = "";

            Frames.push_back(frame);

        } else if (name_frame == "PCNT") {

            std::shared_ptr<PCNT> frame ( new PCNT{name_frame, size_frame_bytes});

            char *size_hex = new char [frame->frame_size_];
            is.read(size_hex, frame->frame_size_);

            uint32_t p_ = frame->frame_size_ - 1;
            uint32_t counter = 0;
            for (int i = 0; i < frame->frame_size_; ++i) {
                counter += uint32_t(size_hex[i]) * pow(InfoSize::kTWO_IN_THE_SEVENTH, p);
                --p_;
            }
            delete[] size_hex;
            frame->counter_ = counter;

            Frames.push_back(frame);

        } else if (name_frame == "POPM") {

            std::shared_ptr<POPM> frame ( new POPM{name_frame, size_frame_bytes});

            std::string email;
            char byte;
            is.read(&byte, 1);
            int count_bytes = 1;

            while ((int) byte != 0) {
                email += byte;
                is.read(&byte, 1);
                ++count_bytes;
            }

            frame->email_to_user_ = email;
            email = "";

            char rating;
            is.read(&rating, InfoSize::kRATING);
            frame->rating_ = int(rating) + 256;

            Frames.push_back(frame);

        } else if (name_frame == "USLT") {

            std::shared_ptr<USLT> frame ( new USLT{name_frame, size_frame_bytes});
            is.read(&frame->text_encoding_, InfoSize::kTEXT_ENCODING);

            char *language_ch = new char [InfoSize::kLANGUAGE];
            is.read(language_ch, InfoSize::kLANGUAGE);
            std::string language;
            for (int i = 0; i < InfoSize::kLANGUAGE; ++i) {
                language += language_ch[i];
            }
            frame->language_ = language;
            delete[] language_ch;

            std::string part_of_data;
            char byte;
            is.read(&byte, 1);
            int count_bytes = 1;

            while ((int) byte != 0) {
                part_of_data += byte;
                is.read(&byte, 1);
                ++count_bytes;
            }

            frame->content_description_ = part_of_data;
            part_of_data = "";

            for (int i = count_bytes; i < frame->frame_size_ - InfoSize::kTEXT_ENCODING - InfoSize::kLANGUAGE; ++i) {
                is.read(&byte, 1);
                part_of_data += byte;
            }
            frame->information_.push_back(part_of_data);
            part_of_data = "";

            Frames.push_back(frame);

        } else if (name_frame == "UFID") {

            std::shared_ptr<UFID> frame ( new UFID{name_frame, size_frame_bytes});

            std::string part_of_data;
            char byte;
            is.read(&byte, 1);
            int count_bytes = 1;

            while ((int) byte != 0) {
                part_of_data += byte;
                is.read(&byte, 1);
                ++count_bytes;
            }

            frame->identifier_ = part_of_data;
            part_of_data = "";

            for (int i = count_bytes; i < frame->frame_size_; ++i) {
                is.read(&byte, 1);
                part_of_data += byte;
            }
            frame->link_ = part_of_data;
            part_of_data = "";

            Frames.push_back(frame);

        } else if (name_frame == "PRIV") {

            std::shared_ptr<PRIV> frame ( new PRIV{name_frame, size_frame_bytes});

            std::string part_of_data;
            char byte;
            is.read(&byte, 1);
            int count_bytes = 1;

            while ((int) byte != 0) {
                part_of_data += byte;
                is.read(&byte, 1);
                ++count_bytes;
            }

            frame->identifier_ = part_of_data;
            part_of_data = "";

            for (int i = count_bytes; i < frame->frame_size_; ++i) {
                is.read(&byte, 1);
                part_of_data += byte;
            }
            frame->link_ = part_of_data;
            part_of_data = "";

            Frames.push_back(frame);

        } else if (name_frame == "LINC") {

            std::shared_ptr<LINK> frame ( new LINK{name_frame, size_frame_bytes});

            char *frame_identifier = new char [InfoSize::kNAME_FRAME];
            is.read(frame_identifier, InfoSize::kNAME_FRAME);
            frame->identifier_ = "";
            for (int i = 0; i < InfoSize::kNAME_FRAME; ++i) {
                frame->identifier_ += frame_identifier[i];
            }
            delete[] frame_identifier;

            std::string part_of_data;
            char byte;
            is.read(&byte, 1);
            int count_bytes = 1;

            while ((int) byte != 0) {
                part_of_data += byte;
                is.read(&byte, 1);
                ++count_bytes;
            }

            frame->link_ = part_of_data;
            part_of_data = "";

            for (int i = count_bytes; i < frame->frame_size_; ++i) {

                char byte_;
                is.read(&byte_, 1);
                if ((int) byte_ == 0) {
                    frame->additional_data_.push_back(part_of_data);
                    part_of_data = "";
                } else {
                    part_of_data += byte_;
                }
                if (i == frame->frame_size_ - 1 && (int) byte_ != 0) {
                    frame->additional_data_.push_back(part_of_data);
                    part_of_data = "";
                }

            }

            Frames.push_back(frame);

        } else if (name_frame == "SEEK") {

            std::shared_ptr<SEEK> frame ( new SEEK{name_frame, size_frame_bytes});

            char *size_hex = new char [frame->frame_size_];
            is.read(size_hex, frame->frame_size_);

            p = frame->frame_size_ - 1;
            uint32_t size_bytes = 0;
            for (int i = 0; i < frame->frame_size_; ++i) {
                size_bytes += uint32_t(size_hex[i]) * pow(InfoSize::kTWO_IN_THE_SEVENTH, p);
                --p;
            }
            delete[] size_hex;
            frame->offset_next_tag_ = size_bytes;

            Frames.push_back(frame);

        } else if (name_frame == "RBUF") {

            std::shared_ptr<RBUF> frame ( new RBUF{name_frame, size_frame_bytes});

            char *size_buf_hex = new char [InfoSize::kBUFFER];
            is.read(size_buf_hex, InfoSize::kBUFFER);

            p = InfoSize::kBUFFER - 1;
            uint32_t size_buf_bytes = 0;
            for (int i = 0; i < InfoSize::kBUFFER; ++i) {
                size_buf_bytes += uint32_t(size_buf_hex[i]) * pow(InfoSize::kTWO_IN_THE_SEVENTH, p);
                --p;
            }
            delete[] size_buf_hex;
            frame->buffer_size_ = size_buf_bytes;

            is.read(&frame->flag_, InfoSize::kBYTE);

            char *size_hex = new char [InfoSize::kSIZE_FRAMES];
            is.read(size_hex, InfoSize::kSIZE_FRAMES);

            p = InfoSize::kSIZE_FRAMES - 1;
            uint32_t size_bytes = 0;
            for (int i = 0; i < frame->frame_size_ - InfoSize::kBUFFER - InfoSize::kBYTE; ++i) {
                size_bytes += uint32_t(size_hex[i]) * pow(InfoSize::kTWO_IN_THE_SEVENTH, p);
                --p;
            }
            delete[] size_hex;
            frame->offset_next_tag_ = size_bytes;

            Frames.push_back(frame);

        } else if (name_frame == "POSS") {

            std::shared_ptr<POSS> frame ( new POSS{name_frame, size_frame_bytes});
            is.read(&frame->time_stamp_format_, InfoSize::kTIME_STAMP_FORMAT);

            char *position_hex = new char [frame->frame_size_ - InfoSize::kTIME_STAMP_FORMAT];
            is.read(position_hex, frame->frame_size_ - InfoSize::kTIME_STAMP_FORMAT);

            p = frame->frame_size_ - InfoSize::kTIME_STAMP_FORMAT - 1;
            uint32_t position_bytes = 0;
            for (int i = 0; i < frame->frame_size_ - InfoSize::kTIME_STAMP_FORMAT; ++i) {
                position_bytes += uint32_t(position_hex[i]) * pow(InfoSize::kTWO_IN_THE_SEVENTH, p);
                --p;
            }
            delete[] position_hex;
            frame->time_stamp_ = position_bytes;

            Frames.push_back(frame);

        } else if (name_frame == "ETCO") {

            std::shared_ptr<ETCO> frame ( new ETCO{name_frame, size_frame_bytes});
            is.read(&frame->time_stamp_format_, InfoSize::kTIME_STAMP_FORMAT);
            is.read(&frame->type_event_, InfoSize::kBYTE);

            char *position_hex = new char [frame->frame_size_ - InfoSize::kTIME_STAMP_FORMAT - InfoSize::kBYTE];
            is.read(position_hex, frame->frame_size_ - InfoSize::kTIME_STAMP_FORMAT - InfoSize::kBYTE);

            p = frame->frame_size_ - InfoSize::kTIME_STAMP_FORMAT - InfoSize::kBYTE - 1;
            uint32_t position_bytes = 0;
            for (int i = 0; i < frame->frame_size_ - InfoSize::kTIME_STAMP_FORMAT - InfoSize::kBYTE; ++i) {
                position_bytes += uint32_t(position_hex[i]) * pow(InfoSize::kTWO_IN_THE_SEVENTH, p);
                --p;
            }
            delete[] position_hex;
            frame->time_stamp_ = position_bytes;

            Frames.push_back(frame);

        } else if (name_frame == "SYLT") {

            std::shared_ptr<SYLT> frame ( new SYLT{name_frame, size_frame_bytes});
            is.read(&frame->text_encoding_, InfoSize::kTEXT_ENCODING);

            char *language_ch = new char [InfoSize::kLANGUAGE];
            is.read(language_ch, InfoSize::kLANGUAGE);
            std::string language;
            for (int i = 0; i < InfoSize::kLANGUAGE; ++i) {
                language += language_ch[i];
            }
            frame->language_ = language;
            delete[] language_ch;

            is.read(&frame->time_stamp_format_, InfoSize::kTIME_STAMP_FORMAT);
            is.read(&frame->content_type_, InfoSize::kCONTENT_TYPE);

            std::string part_of_data;
            char byte;
            is.read(&byte, 1);
            int count_bytes = 1;

            while ((int) byte != 0) {
                part_of_data += byte;
                is.read(&byte, 1);
                ++count_bytes;
            }

            frame->content_description_ = part_of_data;
            part_of_data = "";

            is.read(&byte, 1);
            ++count_bytes;

            while ((int) byte != 0) {
                part_of_data += byte;
                is.read(&byte, 1);
                ++count_bytes;
            }

            frame->sync_identifier_ = part_of_data;
            part_of_data = "";
            uint32_t time_stamp_byte = frame->frame_size_ - InfoSize::kTEXT_ENCODING - InfoSize::kLANGUAGE
                                  - InfoSize::kTIME_STAMP_FORMAT - InfoSize::kCONTENT_TYPE - count_bytes;

            char *position_hex = new char [time_stamp_byte];
            is.read(position_hex, time_stamp_byte);

            p = time_stamp_byte - 1;
            uint32_t position_bytes = 0;
            for (int i = 0; i < time_stamp_byte; ++i) {
                position_bytes += uint32_t(position_hex[i]) * pow(InfoSize::kTWO_IN_THE_SEVENTH, p);
                --p;
            }
            delete[] position_hex;
            frame->time_stamp_ = position_bytes;

            Frames.push_back(frame);

        } else if (name_frame == "ENCR") {

            std::shared_ptr<ENCR> frame ( new ENCR{name_frame, size_frame_bytes});

            std::string part_of_data;
            char byte;
            is.read(&byte, 1);
            int count_bytes = 1;

            while ((int) byte != 0) {
                part_of_data += byte;
                is.read(&byte, 1);
                ++count_bytes;
            }

            frame->owner_identifier_ = part_of_data;
            part_of_data = "";

            is.read(&frame->method_symbol_, InfoSize::kBYTE);

            for (int i = count_bytes; i < frame->frame_size_ - InfoSize::kBYTE; ++i) {
                is.read(&byte, 1);
                part_of_data += byte;
            }
            frame->encryption_data_ = part_of_data;
            part_of_data = "";

            Frames.push_back(frame);

        } else if (name_frame == "GRID") {

            std::shared_ptr<GRID> frame ( new GRID{name_frame, size_frame_bytes});

            std::string part_of_data;
            char byte;
            is.read(&byte, 1);
            int count_bytes = 1;

            while ((int) byte != 0) {
                part_of_data += byte;
                is.read(&byte, 1);
                ++count_bytes;
            }

            frame->owner_identifier_ = part_of_data;
            part_of_data = "";

            is.read(&frame->symbol_group_, InfoSize::kBYTE);

            for (int i = count_bytes; i < frame->frame_size_ - InfoSize::kBYTE; ++i) {
                is.read(&byte, 1);
                part_of_data += byte;
            }
            frame->group_dependent_data_ = part_of_data;
            part_of_data = "";

            Frames.push_back(frame);

        } else if (name_frame == "EQU2") {

            std::shared_ptr<EQU2> frame ( new EQU2{name_frame, size_frame_bytes});
            is.read(&frame->interpolation_method_, InfoSize::kBYTE);

            std::string part_of_data;
            char byte;
            is.read(&byte, 1);

            while ((int) byte != 0) {
                part_of_data += byte;
                is.read(&byte, 1);
            }

            frame->identification_ = part_of_data;
            part_of_data = "";

            char *frequency_hex = new char [InfoSize::kFREQUENCY];
            is.read(frequency_hex, InfoSize::kFREQUENCY);

            p = InfoSize::kFREQUENCY - 1;
            uint32_t frequency_bytes = 0;
            for (int i = 0; i < InfoSize::kFREQUENCY; ++i) {
                frequency_bytes += uint32_t(frequency_hex[i]) * pow(InfoSize::kTWO_IN_THE_SEVENTH, p);
                --p;
            }
            delete[] frequency_hex;
            frame->frequency_ = frequency_bytes;

            char *volume_adjustment_hex = new char [InfoSize::kVOLUME_ADJUSTMENT];
            is.read(volume_adjustment_hex, InfoSize::kFREQUENCY);

            p = InfoSize::kVOLUME_ADJUSTMENT - 1;
            uint32_t volume_adjustment_bytes = 0;
            for (int i = 0; i < InfoSize::kVOLUME_ADJUSTMENT; ++i) {
                volume_adjustment_bytes += uint32_t(volume_adjustment_hex[i]) * pow(InfoSize::kTWO_IN_THE_SEVENTH, p);
                --p;
            }
            delete[] volume_adjustment_hex;
            frame->volume_adjustment_ = volume_adjustment_bytes;

            Frames.push_back(frame);

        } else if (name_frame == "RVA2") {

            std::shared_ptr<RVA2> frame ( new RVA2{name_frame, size_frame_bytes});

            std::string part_of_data;
            char byte;
            is.read(&byte, 1);
            int count_bytes = 1;

            while ((int) byte != 0) {
                part_of_data += byte;
                is.read(&byte, 1);
                ++count_bytes;
            }

            frame->identification_ = part_of_data;
            part_of_data = "";

            is.read(&frame->type_channel_, InfoSize::kBYTE);

            char *volume_adjustment_hex = new char [InfoSize::kVOLUME_ADJUSTMENT];
            is.read(volume_adjustment_hex, InfoSize::kVOLUME_ADJUSTMENT);

            p = InfoSize::kVOLUME_ADJUSTMENT - 1;
            uint32_t volume_adjustment_bytes = 0;
            for (int i = 0; i < InfoSize::kVOLUME_ADJUSTMENT; ++i) {
                volume_adjustment_bytes += uint32_t(volume_adjustment_hex[i]) * pow(InfoSize::kTWO_IN_THE_SEVENTH, p);
                --p;
            }
            delete[] volume_adjustment_hex;
            frame->volume_adjustment_ = volume_adjustment_bytes;

            is.read(&frame->bits_representing_peak_, InfoSize::kBYTE);

            for (int i = count_bytes; i < frame->frame_size_ - InfoSize::kBYTE - InfoSize::kVOLUME_ADJUSTMENT
                                          - InfoSize::kBYTE; ++i) {
                is.read(&byte, 1);
                part_of_data += byte;
            }
            frame->peak_volume_ = part_of_data;
            part_of_data = "";

            Frames.push_back(frame);

        } else if (name_frame == "OWNE") {

            std::shared_ptr<OWNE> frame ( new OWNE{name_frame, size_frame_bytes});
            is.read(&frame->text_encoding_, InfoSize::kTEXT_ENCODING);

            std::string part_of_data;
            char byte;
            is.read(&byte, 1);
            int count_bytes = 1;

            while ((int) byte != 0) {
                part_of_data += byte;
                is.read(&byte, 1);
                ++count_bytes;
            }

            frame->price_ = part_of_data;
            part_of_data = "";

            char *date_ch = new char [InfoSize::kDATE];
            is.read(date_ch, InfoSize::kDATE);
            std::string date;
            for (int i = 0; i < InfoSize::kDATE; ++i) {
                date += date_ch[i];
            }
            frame->date_ = date;
            delete[] date_ch;

            for (int i = count_bytes; i < frame->frame_size_ - InfoSize::kTEXT_ENCODING - InfoSize::kDATE; ++i) {
                is.read(&byte, 1);
                part_of_data += byte;
            }
            frame->seller_ = part_of_data;
            part_of_data = "";

            Frames.push_back(frame);

        } else if (name_frame == "COMR") {

            std::shared_ptr<COMR> frame ( new COMR{name_frame, size_frame_bytes});
            is.read(&frame->text_encoding_, InfoSize::kTEXT_ENCODING);

            std::string part_of_data;
            char byte;
            is.read(&byte, 1);
            int count_bytes = 1;

            while ((int) byte != 0) {
                part_of_data += byte;
                is.read(&byte, 1);
                ++count_bytes;
            }

            frame->price_ = part_of_data;
            part_of_data = "";

            char *date_ch = new char [InfoSize::kDATE];
            is.read(date_ch, InfoSize::kDATE);
            std::string date;
            for (int i = 0; i < InfoSize::kDATE; ++i) {
                date += date_ch[i];
            }
            frame->date_ = date;
            delete[] date_ch;

            is.read(&byte, 1);
            ++count_bytes;
            while ((int) byte != 0) {
                part_of_data += byte;
                is.read(&byte, 1);
                ++count_bytes;
            }

            frame->contact_URL_ = part_of_data;
            part_of_data = "";

            is.read(&frame->received_as_, InfoSize::kBYTE);

            is.read(&byte, 1);
            ++count_bytes;
            while ((int) byte != 0) {
                part_of_data += byte;
                is.read(&byte, 1);
                ++count_bytes;
            }

            frame->seller_ = part_of_data;
            part_of_data = "";

            is.read(&byte, 1);
            ++count_bytes;
            while ((int) byte != 0) {
                part_of_data += byte;
                is.read(&byte, 1);
                ++count_bytes;
            }

            frame->description_ = part_of_data;
            part_of_data = "";

            is.read(&byte, 1);
            ++count_bytes;
            while ((int) byte != 0) {
                part_of_data += byte;
                is.read(&byte, 1);
                ++count_bytes;
            }

            frame->picture_MIME_type_ = part_of_data;
            part_of_data = "";

            for (int i = count_bytes; i < frame->frame_size_ - InfoSize::kTEXT_ENCODING - InfoSize::kDATE
                                          - InfoSize::kBYTE; ++i) {
                is.read(&byte, 1);
                part_of_data += byte;
            }
            frame->seller_logo_ = part_of_data;
            part_of_data = "";

            Frames.push_back(frame);

        }

    }

    return Frames;
}
