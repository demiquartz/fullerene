/** @file
 * @brief ビデオレンダラー
 * @author Takaaki Sato
 * @copyright Copyright (c) 2020 Demiquartz &lt;info@demiquartz.jp&gt; @n
 * Distributed under the MIT License (See accompanying file LICENSE
 * or copy at https://opensource.org/licenses/MIT)
 */
#ifndef FULLERENE_EC3EFB39_0F22_4302_98BC_00BDFD62E7B1
#define FULLERENE_EC3EFB39_0F22_4302_98BC_00BDFD62E7B1

namespace Fullerene::Video {

/**
 * @brief ビデオレンダラーインタフェース
 *
 * 映像を描画するためのインタフェースです。
 */
class Renderer {
public:
    /**
     * @brief デストラクタ
     */
    virtual ~Renderer() {}
};

} // Fullerene::Video

#endif // FULLERENE_EC3EFB39_0F22_4302_98BC_00BDFD62E7B1
