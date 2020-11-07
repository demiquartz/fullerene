/** @file
 * @brief 動作確認用
 * @author Takaaki Sato
 * @copyright Copyright (c) 2020 Demiquartz &lt;info@demiquartz.jp&gt; @n
 * Distributed under the MIT License (See accompanying file LICENSE
 * or copy at https://opensource.org/licenses/MIT)
 */
#include <iostream>
#include "version.hpp"

int main(int argc, char** argv) {
    std::cout << REVISION << std::endl;
    return 0;
}
