/** @file
 * @brief 共通型定義
 * @author Takaaki Sato
 * @copyright Copyright (c) 2020 Demiquartz &lt;info@demiquartz.jp&gt; @n
 * Distributed under the MIT License (See accompanying file LICENSE
 * or copy at https://opensource.org/licenses/MIT)
 */
#ifndef FULLERENE_F26692EF_F2BA_42AE_8586_98B38D4D3F2F
#define FULLERENE_F26692EF_F2BA_42AE_8586_98B38D4D3F2F

#include <cstdint>
#include <boost/qvm/vec.hpp>
#include <boost/qvm/mat.hpp>

namespace Fullerene {

/**
 * @brief 8bit整数型
 */
using i8 = std::int8_t;

/**
 * @brief 16bit整数型
 */
using i16 = std::int16_t;

/**
 * @brief 32bit整数型
 */
using i32 = std::int32_t;

/**
 * @brief 64bit整数型
 */
using i64 = std::int64_t;

/**
 * @brief 32bit浮動小数点数型
 */
using f32 = float;

/**
 * @brief 64bit浮動小数点数型
 */
using f64 = double;

/**
 * @brief 8bit整数2次元ベクトル型
 */
using i8vec2 = boost::qvm::vec<i8, 2>;

/**
 * @brief 8bit整数3次元ベクトル型
 */
using i8vec3 = boost::qvm::vec<i8, 3>;

/**
 * @brief 8bit整数4次元ベクトル型
 */
using i8vec4 = boost::qvm::vec<i8, 4>;

/**
 * @brief 16bit整数2次元ベクトル型
 */
using i16vec2 = boost::qvm::vec<i16, 2>;

/**
 * @brief 16bit整数3次元ベクトル型
 */
using i16vec3 = boost::qvm::vec<i16, 3>;

/**
 * @brief 16bit整数4次元ベクトル型
 */
using i16vec4 = boost::qvm::vec<i16, 4>;

/**
 * @brief 32bit整数2次元ベクトル型
 */
using i32vec2 = boost::qvm::vec<i32, 2>;

/**
 * @brief 32bit整数3次元ベクトル型
 */
using i32vec3 = boost::qvm::vec<i32, 3>;

/**
 * @brief 32bit整数4次元ベクトル型
 */
using i32vec4 = boost::qvm::vec<i32, 4>;

/**
 * @brief 64bit整数2次元ベクトル型
 */
using i64vec2 = boost::qvm::vec<i64, 2>;

/**
 * @brief 64bit整数3次元ベクトル型
 */
using i64vec3 = boost::qvm::vec<i64, 3>;

/**
 * @brief 64bit整数4次元ベクトル型
 */
using i64vec4 = boost::qvm::vec<i64, 4>;

/**
 * @brief 32bit浮動小数点数2次元ベクトル型
 */
using f32vec2 = boost::qvm::vec<f32, 2>;

/**
 * @brief 32bit浮動小数点数3次元ベクトル型
 */
using f32vec3 = boost::qvm::vec<f32, 3>;

/**
 * @brief 32bit浮動小数点数4次元ベクトル型
 */
using f32vec4 = boost::qvm::vec<f32, 4>;

/**
 * @brief 64bit浮動小数点数2次元ベクトル型
 */
using f64vec2 = boost::qvm::vec<f64, 2>;

/**
 * @brief 64bit浮動小数点数3次元ベクトル型
 */
using f64vec3 = boost::qvm::vec<f64, 3>;

/**
 * @brief 64bit浮動小数点数4次元ベクトル型
 */
using f64vec4 = boost::qvm::vec<f64, 4>;

/**
 * @brief 8bit整数2x2行列型
 */
using i8mat2x2 = boost::qvm::mat<i8, 2, 2>;

/**
 * @brief 8bit整数2x3行列型
 */
using i8mat2x3 = boost::qvm::mat<i8, 2, 3>;

/**
 * @brief 8bit整数2x4行列型
 */
using i8mat2x4 = boost::qvm::mat<i8, 2, 4>;

/**
 * @brief 8bit整数3x2行列型
 */
using i8mat3x2 = boost::qvm::mat<i8, 3, 2>;

/**
 * @brief 8bit整数3x3行列型
 */
using i8mat3x3 = boost::qvm::mat<i8, 3, 3>;

/**
 * @brief 8bit整数3x4行列型
 */
using i8mat3x4 = boost::qvm::mat<i8, 3, 4>;

/**
 * @brief 8bit整数4x2行列型
 */
using i8mat4x2 = boost::qvm::mat<i8, 4, 2>;

/**
 * @brief 8bit整数4x3行列型
 */
using i8mat4x3 = boost::qvm::mat<i8, 4, 3>;

/**
 * @brief 8bit整数4x4行列型
 */
using i8mat4x4 = boost::qvm::mat<i8, 4, 4>;

/**
 * @brief 16bit整数2x2行列型
 */
using i16mat2x2 = boost::qvm::mat<i16, 2, 2>;

/**
 * @brief 16bit整数2x3行列型
 */
using i16mat2x3 = boost::qvm::mat<i16, 2, 3>;

/**
 * @brief 16bit整数2x4行列型
 */
using i16mat2x4 = boost::qvm::mat<i16, 2, 4>;

/**
 * @brief 16bit整数3x2行列型
 */
using i16mat3x2 = boost::qvm::mat<i16, 3, 2>;

/**
 * @brief 16bit整数3x3行列型
 */
using i16mat3x3 = boost::qvm::mat<i16, 3, 3>;

/**
 * @brief 16bit整数3x4行列型
 */
using i16mat3x4 = boost::qvm::mat<i16, 3, 4>;

/**
 * @brief 16bit整数4x2行列型
 */
using i16mat4x2 = boost::qvm::mat<i16, 4, 2>;

/**
 * @brief 16bit整数4x3行列型
 */
using i16mat4x3 = boost::qvm::mat<i16, 4, 3>;

/**
 * @brief 16bit整数4x4行列型
 */
using i16mat4x4 = boost::qvm::mat<i16, 4, 4>;

/**
 * @brief 32bit整数2x2行列型
 */
using i32mat2x2 = boost::qvm::mat<i32, 2, 2>;

/**
 * @brief 32bit整数2x3行列型
 */
using i32mat2x3 = boost::qvm::mat<i32, 2, 3>;

/**
 * @brief 32bit整数2x4行列型
 */
using i32mat2x4 = boost::qvm::mat<i32, 2, 4>;

/**
 * @brief 32bit整数3x2行列型
 */
using i32mat3x2 = boost::qvm::mat<i32, 3, 2>;

/**
 * @brief 32bit整数3x3行列型
 */
using i32mat3x3 = boost::qvm::mat<i32, 3, 3>;

/**
 * @brief 32bit整数3x4行列型
 */
using i32mat3x4 = boost::qvm::mat<i32, 3, 4>;

/**
 * @brief 32bit整数4x2行列型
 */
using i32mat4x2 = boost::qvm::mat<i32, 4, 2>;

/**
 * @brief 32bit整数4x3行列型
 */
using i32mat4x3 = boost::qvm::mat<i32, 4, 3>;

/**
 * @brief 32bit整数4x4行列型
 */
using i32mat4x4 = boost::qvm::mat<i32, 4, 4>;

/**
 * @brief 64bit整数2x2行列型
 */
using i64mat2x2 = boost::qvm::mat<i64, 2, 2>;

/**
 * @brief 64bit整数2x3行列型
 */
using i64mat2x3 = boost::qvm::mat<i64, 2, 3>;

/**
 * @brief 64bit整数2x4行列型
 */
using i64mat2x4 = boost::qvm::mat<i64, 2, 4>;

/**
 * @brief 64bit整数3x2行列型
 */
using i64mat3x2 = boost::qvm::mat<i64, 3, 2>;

/**
 * @brief 64bit整数3x3行列型
 */
using i64mat3x3 = boost::qvm::mat<i64, 3, 3>;

/**
 * @brief 64bit整数3x4行列型
 */
using i64mat3x4 = boost::qvm::mat<i64, 3, 4>;

/**
 * @brief 64bit整数4x2行列型
 */
using i64mat4x2 = boost::qvm::mat<i64, 4, 2>;

/**
 * @brief 64bit整数4x3行列型
 */
using i64mat4x3 = boost::qvm::mat<i64, 4, 3>;

/**
 * @brief 64bit整数4x4行列型
 */
using i64mat4x4 = boost::qvm::mat<i64, 4, 4>;

/**
 * @brief 32bit浮動小数点数2x2行列型
 */
using f32mat2x2 = boost::qvm::mat<f32, 2, 2>;

/**
 * @brief 32bit浮動小数点数2x3行列型
 */
using f32mat2x3 = boost::qvm::mat<f32, 2, 3>;

/**
 * @brief 32bit浮動小数点数2x4行列型
 */
using f32mat2x4 = boost::qvm::mat<f32, 2, 4>;

/**
 * @brief 32bit浮動小数点数3x2行列型
 */
using f32mat3x2 = boost::qvm::mat<f32, 3, 2>;

/**
 * @brief 32bit浮動小数点数3x3行列型
 */
using f32mat3x3 = boost::qvm::mat<f32, 3, 3>;

/**
 * @brief 32bit浮動小数点数3x4行列型
 */
using f32mat3x4 = boost::qvm::mat<f32, 3, 4>;

/**
 * @brief 32bit浮動小数点数4x2行列型
 */
using f32mat4x2 = boost::qvm::mat<f32, 4, 2>;

/**
 * @brief 32bit浮動小数点数4x3行列型
 */
using f32mat4x3 = boost::qvm::mat<f32, 4, 3>;

/**
 * @brief 32bit浮動小数点数4x4行列型
 */
using f32mat4x4 = boost::qvm::mat<f32, 4, 4>;

/**
 * @brief 64bit浮動小数点数2x2行列型
 */
using f64mat2x2 = boost::qvm::mat<f64, 2, 2>;

/**
 * @brief 64bit浮動小数点数2x3行列型
 */
using f64mat2x3 = boost::qvm::mat<f64, 2, 3>;

/**
 * @brief 64bit浮動小数点数2x4行列型
 */
using f64mat2x4 = boost::qvm::mat<f64, 2, 4>;

/**
 * @brief 64bit浮動小数点数3x2行列型
 */
using f64mat3x2 = boost::qvm::mat<f64, 3, 2>;

/**
 * @brief 64bit浮動小数点数3x3行列型
 */
using f64mat3x3 = boost::qvm::mat<f64, 3, 3>;

/**
 * @brief 64bit浮動小数点数3x4行列型
 */
using f64mat3x4 = boost::qvm::mat<f64, 3, 4>;

/**
 * @brief 64bit浮動小数点数4x2行列型
 */
using f64mat4x2 = boost::qvm::mat<f64, 4, 2>;

/**
 * @brief 64bit浮動小数点数4x3行列型
 */
using f64mat4x3 = boost::qvm::mat<f64, 4, 3>;

/**
 * @brief 64bit浮動小数点数4x4行列型
 */
using f64mat4x4 = boost::qvm::mat<f64, 4, 4>;

} // Fullerene

#endif // FULLERENE_F26692EF_F2BA_42AE_8586_98B38D4D3F2F
