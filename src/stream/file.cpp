/**
 * @brief ファイル入出力
 * @author Takaaki Sato
 * @copyright Copyright (c) 2020 Demiquartz &lt;info@demiquartz.jp&gt;@n
 * Distributed under the MIT License (See accompanying file LICENSE
 * or copy at https://opensource.org/licenses/MIT)
 */
#include <cstdio>
#include <sys/stat.h>
#include "file.hpp"

namespace Fullerene::Stream {

class File final : public Stream {
public:
    File(const std::string& path, const std::string& mode) : Handle_(std::fopen(path.c_str(), (mode.find('b') == std::string::npos ? mode + 'b' : mode).c_str())) {
    }

    virtual ~File() override {
        if (Handle_) std::fclose(Handle_);
    }

    virtual explicit operator bool() const override {
        return Handle_ != nullptr;
    }

    virtual std::size_t Size(void) override {
        struct stat s;
        return fstat(fileno(Handle_), &s) == 0 ? s.st_size : 0;
    }

    virtual std::size_t Read(void* data, std::size_t size) override {
        return std::fread(data, 1, size, Handle_);
    }

    virtual std::size_t Write(const void* data, std::size_t size) override {
        return std::fwrite(data, 1, size, Handle_);
    }

    virtual bool Flush(void) override {
        return std::fflush(Handle_) == 0;
    }

    virtual bool Seek(std::size_t offset) override {
        return std::fseek(Handle_, offset, SEEK_SET);
    }

    virtual std::size_t Tell(void) override {
        return std::ftell(Handle_);
    }

private:
    FILE* Handle_;
};

std::shared_ptr<Stream> FileFactory::Open(const std::string& path, const std::string& mode) {
    return std::make_shared<File>(path, mode);
}

} // namespace Fullerene::Stream
