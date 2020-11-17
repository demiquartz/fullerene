/** @file
 * @brief ビデオレンダラー
 * @author Takaaki Sato
 * @copyright Copyright (c) 2020 Demiquartz &lt;info@demiquartz.jp&gt; @n
 * Distributed under the MIT License (See accompanying file LICENSE
 * or copy at https://opensource.org/licenses/MIT)
 */
#ifndef INCLUDED_581C6CEE_99E5_4E3A_A8EC_003FFD69B5C4
#define INCLUDED_581C6CEE_99E5_4E3A_A8EC_003FFD69B5C4

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

#endif // INCLUDED_581C6CEE_99E5_4E3A_A8EC_003FFD69B5C4
