/** @file
 * @brief ビデオレンダラー(Vulkan)
 * @author Takaaki Sato
 * @copyright Copyright (c) 2020 Demiquartz &lt;info@demiquartz.jp&gt; @n
 * Distributed under the MIT License (See accompanying file LICENSE
 * or copy at https://opensource.org/licenses/MIT)
 */
#ifndef FULLERENE_1BF10221_6A1A_4E19_84F1_CE018A6D320A
#define FULLERENE_1BF10221_6A1A_4E19_84F1_CE018A6D320A

#include <memory>
#include "../renderer.hpp"

namespace Fullerene::Video::Detail {

/**
 * @brief ビデオレンダラークラス(Vulkan)
 *
 * Vulkanを使用して映像を描画します。
 */
class Vulkan final : public Renderer {
public:
    /**
     * @brief コンストラクタ
     */
    Vulkan();

private:
    struct Impl;
    std::shared_ptr<Impl> spImpl_;
    static std::weak_ptr<Impl> wpImpl_;
};

} // Fullerene::Video::Detail

#endif // FULLERENE_1BF10221_6A1A_4E19_84F1_CE018A6D320A
