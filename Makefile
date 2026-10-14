# 競プロ用の補助ターゲット。
#   make            … solver/main.cpp をビルドする
#   make submit     … solver/main.cpp を ACL ごと 1 ファイルに展開して solver/main.submit.cpp を作る
#
# SRC は上書きできる。コンテストのディレクトリでは SRC だけ渡せばよい。
#   make build  SRC=ABC/A.cpp    … ABC/A を作る
#   make submit SRC=ABC/A.cpp    … ABC/A.submit.cpp を作る
# 出力先を変えたいときだけ OUT も渡す。

# LIB は ei1333/library を無改変で置いた submodule (docs/makefile.md を参照)。
LIB      := ei1333-library
ACL      := ac-library
CXX      := g++
CXXFLAGS := -std=gnu++20 -O2 -Wall -Wextra -Wno-sign-compare -I"$(ACL)" -I"$(LIB)"

SRC ?= solver/main.cpp
# OUT を指定しなければ、SRC の隣に <名前>.submit.cpp を作る。
# 例: SRC=ABC/A.cpp なら ABC/A.submit.cpp
OUT ?= $(SRC:.cpp=.submit.cpp)

.PHONY: build submit clean

build: $(SRC)
	$(CXX) $(CXXFLAGS) "$(SRC)" -o "$(basename $(SRC))"

# ライブラリ (ei1333-library) と ACL の両方を展開する (Codeforces などでも出せるように)。
# oj-bundle は #include <...> を展開しないので、ACL は同梱の expander.py で展開する。
submit: $(SRC)
	set -o pipefail; oj-bundle -I "$(LIB)" "$(SRC)" | python3 "$(ACL)/expander.py" --lib "$(ACL)" -c /dev/stdin > "$(OUT)"
	@echo "generated $(OUT) from $(SRC)"

clean:
	rm -f "$(OUT)" "$(basename $(SRC))"
