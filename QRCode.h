// Biblioteca a qual está implementada a função CodigosCorretores( ) que retorna os códigos corretores utilizados
// para a criação de códigos QR.
//
// A função retorna o endereço do 1º elemento de um vetor que contém os Códigos Corretores de Erro (Error Correc-
// tion Codewords), onde o programa (ou a função) que chamar CodigosCorretores( ) deverá liberar a memória aloca-
// da dinamicamente por CodigosCorretores( ) através da função free( ).
//
// Onde:
//      mensagem: vetor que representa os coeficientes da mensagem
//      tamMens:  número de elementos do vetor mensagem
//      N_corretores: número de códigos corretores de erro (Error Correction Codewords)

unsigned char *CodigosCorretores(unsigned short mensagem[], unsigned short tamMens, unsigned short NumCodigos);


// ----------------------------------------------------------------------------------------------------------


// A função CodigosCorretoresStringFormat( ) retorna o endereço do 1º carácter de uma string que contém os Có-
// digos Corretores de Erro (Error Correction Codewords) da String Format, onde o trecho de código que chamar
// essa função deverá liberar a memória aloca.
//
// Onde:
//      str: string que contém 5 bits (2 primeiros bits indicam o Error Correction Level e  os 3 últimos bits
//           representam o Mask Pattern bits.

unsigned char *CodigosCorretoresStringFormat(char str[]);
