/**
 * @brief 動作確認用
 * @author Takaaki Sato
 * @copyright Copyright (c) 2020 Demiquartz &lt;info@demiquartz.jp&gt; @n
 * Distributed under the MIT License (See accompanying file LICENSE
 * or copy at https://opensource.org/licenses/MIT)
 */
#include <iostream>
#include <string>
#include <vector>
#include "stream/file.hpp"
#include "video/renderer/vulkan.hpp"
#include "version.hpp"

int main(int argc, char** argv) {
    std::cout << REVISION << std::endl << std::endl;
    auto fileFactory = std::make_shared<Fullerene::Stream::FileFactory>();
    auto file        = fileFactory->Open("../LICENSE", "r");
    if (!file) return EXIT_FAILURE;
    std::vector<char> text(file->Size());
    if (file->Read(text.data(), text.size()) != text.size()) return EXIT_FAILURE;
    std::cout << std::string_view(text.data(), text.size()) << std::endl;
    {
        {
            Fullerene::Video::Detail::Vulkan renderer;
            Fullerene::Video::Detail::Vulkan renderer1;
            Fullerene::Video::Detail::Vulkan renderer2;
        }
        Fullerene::Video::Detail::Vulkan renderer3;
        {
            Fullerene::Video::Detail::Vulkan renderer4;
            Fullerene::Video::Detail::Vulkan renderer5;
            Fullerene::Video::Detail::Vulkan renderer6;
        }
        Fullerene::Video::Detail::Vulkan renderer7;
    }
    return EXIT_SUCCESS;
}
