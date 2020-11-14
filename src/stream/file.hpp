/** @file
 * @brief ファイル入出力
 * @author Takaaki Sato
 * @copyright Copyright (c) 2020 Demiquartz &lt;info@demiquartz.jp&gt;@n
 * Distributed under the MIT License (See accompanying file LICENSE
 * or copy at https://opensource.org/licenses/MIT)
 */
#ifndef INCLUDED_8F483776_2C56_4E98_8199_5504417D01EE
#define INCLUDED_8F483776_2C56_4E98_8199_5504417D01EE

#include "stream.hpp"

namespace Fullerene::Stream {

/**
 * @brief ファイルファクトリクラス
 *
 * ファイルを読み書きするためのファクトリクラスです。
 */
class FileFactory final : public StreamFactory {
public:
    /**
     * @brief ファイルを開く
     *
     * パスで指定したファイルを開きます。@n
     * オープンモードは以下の6つをサポートしています。
     * -# "r"@n
     *    読み込みモードで開きます。@n
     *    ファイルが存在しない場合は失敗します。
     * -# "w"@n
     *    書き込みモードで開きます。@n
     *    ファイルが存在しない場合は新規作成します。@n
     *    ファイルが存在する場合は初期化されます。
     * -# "a"@n
     *    書き込みモードで開きます。@n
     *    ファイルが存在しない場合は新規作成します。@n
     *    ファイルが存在する場合は追記されます。
     * -# "r+"@n
     *    読み書きモードで開きます。@n
     *    ファイルが存在しない場合は失敗します。
     * -# "w+"@n
     *    読み書きモードで開きます。@n
     *    ファイルが存在しない場合は新規作成します。@n
     *    ファイルが存在する場合は初期化されます。
     * -# "a+"@n
     *    読み書きモードで開きます。@n
     *    ファイルが存在しない場合は新規作成します。@n
     *    ファイルが存在する場合は追記されます。
     *
     * fopenの形式に合わせていますが、[テキスト|バイナリ]の区別はされません。@n
     * バイナリモードのみをサポートし、"b"オプションは記述不要です。
     *
     * @param [in] path ファイルパス
     * @param [in] mode オープンモード
     *
     * @return Streamオブジェクトの共有ポインタ
     * @throw std::system_error Streamオブジェクトの作成に失敗
     */
    virtual StreamPointer Open(const std::string& path, const std::string& mode) override;
};

} // namespace Fullerene::Stream

#endif // INCLUDED_8F483776_2C56_4E98_8199_5504417D01EE
