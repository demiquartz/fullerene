/** @file
 * @brief 数学ライブラリ
 * @author Takaaki Sato
 * @copyright Copyright (c) 2020 Demiquartz &lt;info@demiquartz.jp&gt; @n
 * Distributed under the MIT License (See accompanying file LICENSE
 * or copy at https://opensource.org/licenses/MIT)
 */
#ifndef FULLERENE_3B47EA0B_8CC7_4715_9074_318DADECFA0B
#define FULLERENE_3B47EA0B_8CC7_4715_9074_318DADECFA0B

#include <complex>
#include <boost/qvm/all.hpp>
#include <fullerene/types.hpp>

namespace Fullerene {

/**
 * @brief 複素数型
 *
 * @tparam T 数値型
 */
template<typename T>
using complex = std::complex<T>;

/**
 * @brief 四元数型
 *
 * @tparam T 数値型
 */
template<typename T>
using quaternion = boost::qvm::quat<T>;

} // Fullerene

#endif // FULLERENE_3B47EA0B_8CC7_4715_9074_318DADECFA0B
