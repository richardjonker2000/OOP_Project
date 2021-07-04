///////////////TData.h////////////////
// apenas permite representar datas a partir do ano 100
// atualização: 3/Out/2013 (passaram tb a existir as classes THora e TDataHora) 
// atualização: 15/Out/2013 (construtor por defeito deixou de criar o objecto com a data atual;
//							 sempre que um método receba como parâmetro a string "HOJE", em vez
//							 de uma data, essa string é interpretada como representando a data atual)
// atualização: 11/Nov/2014 (passaram tb a existir os métodos para devolução do mês em formato de string) 
// atualização: 12/Nov/2014 (os métdodos getIdade, getDiaDaSemana, getdiaDaSemana, getMesDoAno e getmesDoAno perderam o prefixo get) 

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
	string DiaDaSemana() const;			// devolve uma string com o dia da semana iniciado em maiúscula
	string diaDaSemana() const;			// devolve uma string com o dia da semana iniciado em minúscula
	string MesDoAno() const;				// devolve uma string com o mês do ano iniciado em maiúscula
	string mesDoAno() const;				// devolve uma string com o mês do ano iniciado em minúscula
	int getDia() const;
	int getMes() const;
	int getAno() const;
	int idade() const;					//só faz sentido se o objeto for uma data de nascimento
	bool bissexto() const;
	int ultimoDiadoMes() const;				//devolve o último dia do mês da data representada no objeto atual
	int diaDoAno() const;					//devolve o dia do ano da data representada no objeto atual
	long diasJaPassados() const;			//devolve os dias que já passaram desde a data representada no objeto atual até ao dia de hoje
	long operator-(const TData &outra) const;//devolve o nº de dias entre a data 'outra' e a data representada no objeto atual
	bool operator<(const TData &outra) const;
	bool operator>(const TData &outra) const;
	bool operator==(const TData &outra) const;
	bool operator!=(const TData &outra) const;
	bool operator<=(const TData &outra) const;
	bool operator>=(const TData &outra) const;
	static TData hoje();
private:									// Métodos estáticos auxiliares
	static bool dataValida(int d, int m, int a);
	static bool bissexto(int a);
	static int ultimoDiadoMes(int m, int a);
};

ostream &operator<<(ostream &os, const TData &dat);
istream &operator>>(istream &is, TData &dat);
