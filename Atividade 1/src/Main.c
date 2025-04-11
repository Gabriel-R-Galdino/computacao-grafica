#include "Biblioteca.h"

int main() {
    if (!carregar_imagem()) return 1;

    ler_cabecalho();
    ler_imagem();
    fclose(fpin);

    gerar_media_simples();
    gerar_media_ponderada();
    gerar_negativo();

    liberar_memoria();

    printf("Imagens geradas com sucesso!\n");

    return 0;
}
