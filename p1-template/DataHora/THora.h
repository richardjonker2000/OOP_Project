///////////////THora.h////////////////
// permite representar um tempo, com horas, minutos e segundos
// atualização: 3/Out/2013
// atualização: 15/Out/2013 (construtor por defeito deixou de criar o objecto com a hora atual;
//							 sempre que um método receba como parâmetro a string "AGORA", em vez
//							 de um tempo, essa string é interpretada como representando a hora atual)


#pragma once
#include<string>
#include<ctime>
using namespace std;

class THora{
protected:
	int hora, minuto;
	double segundo;
public:
	THora();								
	THora(int h, int m, double s);			// cria o objeto com o tempo h:m:s
	THora(const string & temp);				// cria o objeto com o tempo expresso na string temp (string com um tempo no formato "xx:xx:xx.x")
	THora(const char *temp);				// cria o objeto com a tempo expresso na string tipo C temp (string com um tempo no formato "xx:xx:xx.x")
	bool setHora(int h);
	bool setMinuto(int m);
	bool setSegundo(double d);
	virtual bool set(int h, int m, double s);
	virtual void set(const string &temp);	// temp: string com um tempo no formato "xx:xx:xx.x"
	void operator=(const string &temp);		// temp: string com um tempo no formato "xx:xx:xx.x"
	string tempo_str() const;				// devolve uma string com a tempo no formato "xx:xx:xx.x"
	int getHora() const;
	int getMinuto() const;
	double getSegundo() const;
	double totalHoras() const;				//devolve o tempo convertido para horas
	double totalMinutos() const;			//devolve o tempo convertido para minutos
	double totalSegundos() const;			//devolve o tempo convertido para segundos
	THora operator-(const THora &outra) const; //devolve o tempo decorrido entre a hora 'outra' e a hora representada no objeto atual
											   //devolve o tempo 0:0:0 se a hora 'outra' for maior que a hora representada no objeto atual
	THora operator+(const THora &outra) const;
	bool operator<(const THora &outra) const;
	bool operator>(const THora &outra) const;
	bool operator==(const THora &outra) const;
	bool operator!=(const THora &outra) const;
	bool operator<=(const THora &outra) const;
	bool operator>=(const THora &outra) const;
	static THora agora();
private:									// Métodos estáticos auxiliares
	static bool tempoValido(int h, int m, double s);
};

ostream &operator<<(ostream &os, const THora &temp);
istream &operator>>(istream &is, THora &temp);