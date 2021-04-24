Requisitos
=============

* gcc >= 8.2
* cmake3
* no caso dos unit tests, precisa gtest

Comandos
=============

A partir do diretorio base:

`mkdir build; cd build; cmake3 ..; make`

No caso de solicitar o build dos unit tests:

`mkdir build; cd build; cmake3 .. -DUNIT_TEST=ON; make`

Saída
=============

Após build, os arquivos a seguir serão gerados:

* guessing_game: executável com o jogo
* libgg.a: biblioteca com o código para desenvolvimento
* guessing_game_test: no caso dos testes, este é o executável para validar o código

