/** @file
 * @brief ビデオレンダラー(Vulkan)
 * @author Takaaki Sato
 * @copyright Copyright (c) 2020 Demiquartz &lt;info@demiquartz.jp&gt; @n
 * Distributed under the MIT License (See accompanying file LICENSE
 * or copy at https://opensource.org/licenses/MIT)
 */
#ifndef INCLUDED_910AE0CF_5318_4A20_A222_9B613F996E45
#define INCLUDED_910AE0CF_5318_4A20_A222_9B613F996E45

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

#endif // INCLUDED_910AE0CF_5318_4A20_A222_9B613F996E45
