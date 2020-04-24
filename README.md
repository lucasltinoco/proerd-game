# proerd-game 

Este projeto foi parte dos requisitos para a aprovação na disciplina de Programação em C no curso técnico em eletrônica integrado ao ensino médio do Instituto Federal de Santa Catarina.
O projeto consiste em um jogo programado em C utilizando a biblioteca Allegro 5. 

## Executando o jogo no Linux

Tendo a biblioteca Allegro 5 e o compilador GCC instalados, basta executar os seguintes comandos no terminal:


```console
g++ -Wall -g proerd_game.cpp -lm `pkg-config --cflags --libs allegro-5 allegro_acodec-5 allegro_audio-5 allegro_color-5 allegro_dialog-5 allegro_font-5 allegro_image-5 allegro_main-5 allegro_memfile-5 allegro_physfs-5 allegro_primitives-5 allegro_ttf-5`
```

```console
./a.out
```
