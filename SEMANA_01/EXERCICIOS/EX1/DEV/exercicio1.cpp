#include <iostream>
#include <string>
using namespace std;


// 1) Faça uma função que receba 3 valores: um valor mínimo, um valor máximo e um terceiro valor. 
// A função deve retornar se o terceiro valor inserido está mais próximo do valor mínimo ou do máximo, 
// em porcentagem 

// a variável medida, primeiro se iguala aos valores inseridos, depois armazena a porcentagem em relação ao intervalo
int converteSensor(int medida, int num1, int num2){
  int intervaloCompleto = num2 - num1;
  medida = medida - num1;
  medida = (medida * 100) / intervaloCompleto;

  return medida;
}


// 2) Faça uma função que recebe um número inteiro e retorna este valor inserido em formato de return

int sensor(){
  int medida;

  cout << "Insira um número inteiro: ";
  cin >> medida;

  return medida;
}


// 3) Faça uma função que que insere novos valores em um vetor cujos argumentos serão: valor a ser inserido, 
// capacidade de armazenamento de valores (número de posições), qual foi a última posição preenchida e o 
// nome do vetor criado. A função funcionará como um "append" do Python controlado

int insereLista(int novoValor, int ultimaPosicao, int *v, int tamanhoMax){
    int *lista = v;
    lista[tamanhoMax];
    lista[ultimaPosicao] = novoValor;
    return ultimaPosicao+1;
}


// 4) Faça uma função que recebe um vetor com 4 valores numéricos que representam "distâncias": Direita, 
// esquerda, frente e trás e retorna qual destes valores (direita, etc) é o maior.

const char* direcaoMenorCaminho(int *lista, int *valorMax){

  const char* direcoes[] = {"Direita", "Esquerda", "Frente", "Trás"};

  int posicao = 0;

  for(int i = 0; i < 4; i++){
    if (lista[i] > *valorMax){
      *valorMax = lista[i];
      posicao = i;
    }
  }

  return direcoes[posicao];
}


// 5) Faça uma função que lê os valores 0 e 1, ficando em loop até que o valor 0 seja lido

bool leComando(){
  char resposta;

  cout << "Deseja continuar? S/N";
  cin >> resposta;

  if(resposta == 'N' || resposta == 'n'){
    return false;
  }

  return true;
}


// 6 - A função abaixo (que está incompleta) vai "dirigindo" virtualmente um robô e através de 4 sensores
//  em cada um dos 4 pontos do robo ("Direita", "Esquerda", "Frente", "Tras"). A cada passo, ele verifica 
// as distâncias aos objetos e vai mapeando o terreno para uma movimentação futura. Ele vai armazenando 
// estas distancias em um vetor fornecido como parâmetro e retorna a ultima posicao preenchida do vetor. 
// Esta função deve ir lendo os 4 sensores até que um comando de pare seja enviado. Para simular os 
// sensores e os comandos de pare, use as funções já construídas nos ítens anteriores e em um looping 
// contínuo até que um pedido de parada seja enviado pelo usuário. Complete a função com a chamada das 
// funções já criadas

int dirige(int *v,int maxv){
	int maxVetor = maxv;
	int *vetorMov = v;
	int posAtualVetor = 0;
	int dirigindo = 1;		
  
	while(dirigindo){		
        for(int i = 0; i < 4; i++){
		    int medida = sensor();
		    medida = converteSensor(medida,0,830);
		    posAtualVetor = insereLista(medida, posAtualVetor, vetorMov, maxVetor);
        }
    
	    dirigindo = leComando();	
    }

	return posAtualVetor;
}

void percorre(int *v,int tamPercorrido){		
	int *vetorMov = v;
	int maiorDir = 0;
	
	for(int i = 0; i< tamPercorrido; i+=4){
		const char *direcao = direcaoMenorCaminho(&(vetorMov[i]),&maiorDir);
		printf("Movimentando para %s distancia = %i\n",direcao,maiorDir);
	}
}

int main(int argc, char** argv) {
	int maxVetor = 100;
	int vetorMov[maxVetor*4];
	int posAtualVet = 0;
	
	posAtualVet = dirige(vetorMov,maxVetor);
	percorre(vetorMov,posAtualVet);
	
	return 0;
}