cmake -S. -Bbuild -DCMAKE_CXX_COMPILER=mpic++ -DCMAKE_BUILD_TYPE=Debug

- -S. ソースディレクトリを指定する。この場合、カレントディレクトリを指定している
- -Bbuild ビルドディレクトリを指定する。この場合、カレントディレクトリのbuildディレクトリを指定している。このディレクトリが存在しない場合、cmakeによって自動的に作成される
- -DCMAKE_CXX_COMPILER=mpic++ MPIを使用する場合、C++コンパイラを指定する。この場合、mpic++を指定している
- -DCMAKE_BUILD_TYPE=Debug ビルドタイプを指定する。この場合、デバッグビルドを指定している。最適化が無効化され、デバッグ情報が付加される
