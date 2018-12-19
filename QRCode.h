// Biblioteca a qual est� implementada a fun��o CodigosCorretores( ) que retorna os c�digos corretores utilizados
// para a cria��o de c�digos QR.
//
// A fun��o retorna o endere�o do 1� elemento de um vetor que cont�m os C�digos Corretores de Erro (Error Correc-
// tion Codewords), onde o programa (ou a fun��o) que chamar CodigosCorretores( ) dever� liberar a mem�ria aloca-
// da dinamicamente por CodigosCorretores( ) atrav�s da fun��o free( ).
//
// Onde:
//      mensagem: vetor que representa os coeficientes da mensagem
//      tamMens:  n�mero de elementos do vetor mensagem
//      N_corretores: n�mero de c�digos corretores de erro (Error Correction Codewords)

unsigned char *CodigosCorretores(unsigned short mensagem[], unsigned short tamMens, unsigned short NumCodigos);


// ----------------------------------------------------------------------------------------------------------


// A fun��o CodigosCorretoresStringFormat( ) retorna o endere�o do 1� car�cter de uma string que cont�m os C�-
// digos Corretores de Erro (Error Correction Codewords) da String Format, onde o trecho de c�digo que chamar
// essa fun��o dever� liberar a mem�ria aloca.
//
// Onde:
//      str: string que cont�m 5 bits (2 primeiros bits indicam o Error Correction Level e  os 3 �ltimos bits
//           representam o Mask Pattern bits.

unsigned char *CodigosCorretoresStringFormat(char str[]);
