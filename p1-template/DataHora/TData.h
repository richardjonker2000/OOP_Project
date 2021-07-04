///////////////TData.h////////////////
// apenas permite representar datas a partir do ano 100
// atualiza��o: 3/Out/2013 (passaram tb a existir as classes THora e TDataHora) 
// atualiza��o: 15/Out/2013 (construtor por defeito deixou de criar o objecto com a data atual;
//							 sempre que um m�todo receba como par�metro a string "HOJE", em vez
//							 de uma data, essa string � interpretada como representando a data atual)
// atualiza��o: 11/Nov/2014 (passaram tb a existir os m�todos para devolu��o do m�s em formato de string) 
// atualiza��o: 12/Nov/2014 (os m�tdodos getIdade, getDiaDaSemana, getdiaDaSemana, getMesDoAno e getmesDoAno perderam o prefixo get) 

#pragma once
#include<string>
#include<ctime>
using namespace std;

class TData{
protected:
	int dia, mes, ano;
public:
	TData();								
	TData(int d, int m, int a);				// cria o objeto com a data d/m/a
	TData(const string & dat);				// cria o objeto com a data expressa na string dat (string com uma data no formato "x/x/xxxx" ou "x-x-xx")
	TData(const char *dat);					// cria o objeto com a data expressa na string tipo C dat (string com uma data no formato "x/x/xxxx" ou "x-x-xx")
	bool setDia(int d);
	bool setMes(int m);
	bool setAno(int a);
	virtual bool set(int d, int m, int a);
	virtual void set(const string &dat);	// dat: string com uma data no formato "x/x/xxxx" ou "x-x-xx"
	void operator=(const string &dat);		// dat: string com uma data no formato "x/x/xxxx" ou "x-x-xx"
	string data_str() const;				// devolve uma string com a data no formato "x/Mes/xx"
	string DiaDaSemana() const;			// devolve uma string com o dia da semana iniciado em mai�scula
	string diaDaSemana() const;			// devolve uma string com o dia da semana iniciado em min�scula
	string MesDoAno() const;				// devolve uma string com o m�s do ano iniciado em mai�scula
	string mesDoAno() const;				// devolve uma string com o m�s do ano iniciado em min�scula
	int getDia() const;
	int getMes() const;
	int getAno() const;
	int idade() const;					//s� faz sentido se o objeto for uma data de nascimento
	bool bissexto() const;
	int ultimoDiadoMes() const;				//devolve o �ltimo dia do m�s da data representada no objeto atual
	int diaDoAno() const;					//devolve o dia do ano da data representada no objeto atual
	long diasJaPassados() const;			//devolve os dias que j� passaram desde a data representada no objeto atual at� ao dia de hoje
	long operator-(const TData &outra) const;//devolve o n� de dias entre a data 'outra' e a data representada no objeto atual
	bool operator<(const TData &outra) const;
	bool operator>(const TData &outra) const;
	bool operator==(const TData &outra) const;
	bool operator!=(const TData &outra) const;
	bool operator<=(const TData &outra) const;
	bool operator>=(const TData &outra) const;
	static TData hoje();
private:									// M�todos est�ticos auxiliares
	static bool dataValida(int d, int m, int a);
	static bool bissexto(int a);
	static int ultimoDiadoMes(int m, int a);
};

ostream &operator<<(ostream &os, const TData &dat);
istream &operator>>(istream &is, TData &dat);
