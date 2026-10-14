# 競プロ用の補助ターゲット。
#   make            … main.cpp をビルドする
#   make submit     … main.cpp を ACL ごと 1 ファイルに展開して main.submit.cpp を作る
#   make verify     … Library Checker でライブラリの使い方を検証する
#   make verify T=inv_of_formal_power_series … テストを 1 つだけ検証する
#
# SRC は上書きできる。コンテストのディレクトリでは SRC だけ渡せばよい。
#   make build  SRC=ABC/A.cpp    … ABC/A を作る
#   make submit SRC=ABC/A.cpp    … ABC/A.submit.cpp を作る
# 出力先を変えたいときだけ OUT も渡す。

# LIB は ei1333/library を無改変で clone したもの (docs/makefile.md を参照)。
LIB      := ei1333-library
ACL      := ac-library
CXX      := g++
CXXFLAGS := -std=gnu++20 -O2 -Wall -Wextra -Wno-sign-compare -I"$(ACL)" -I"$(LIB)"

SRC ?= main.cpp
# OUT を指定しなければ、SRC の隣に <名前>.submit.cpp を作る。
# 例: SRC=ABC/A.cpp なら ABC/A.submit.cpp
OUT ?= $(SRC:.cpp=.submit.cpp)
T   ?=

.PHONY: build submit verify clean

build: $(SRC)
	$(CXX) $(CXXFLAGS) "$(SRC)" -o "$(basename $(SRC))"

# ライブラリ (ei1333-library) と ACL の両方を展開する (Codeforces などでも出せるように)。
# oj-bundle は #include <...> を展開しないので、ACL は同梱の expander.py で展開する。
submit: $(SRC)
	set -o pipefail; oj-bundle -I "$(LIB)" "$(SRC)" | python3 "$(ACL)/expander.py" --lib "$(ACL)" -c /dev/stdin > "$(OUT)"
	@echo "generated $(OUT) from $(SRC)"

# oj-verify はカレントディレクトリ以下を再帰的に探して *.test.cpp を実行する。
# リポジトリ直下で実行すると ei1333-library 自身のテストまで拾うので、
# verify/ に cd してから実行する。
verify:
	cd verify && oj-verify run $(if $(T),test/$(T).test.cpp,)

clean:
	rm -f "$(OUT)" "$(basename $(SRC))"
