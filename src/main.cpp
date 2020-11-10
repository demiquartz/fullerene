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
#include "version.hpp"

int main(int argc, char** argv) {
    std::cout << REVISION << std::endl << std::endl;
    Fullerene::Stream::FileFactory fileFactory;
    auto file = fileFactory.Open("../LICENSE", "r");
    if (!file) return EXIT_FAILURE;
    std::vector<char> text(file->Size());
    if (file->Read(text.data(), text.size()) != text.size()) return EXIT_FAILURE;
    std::cout << std::string_view(text.data(), text.size()) << std::endl;
    return EXIT_SUCCESS;
}
