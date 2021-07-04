///////////////TDataHora.cpp (vrs. 12/Nov/2014)////////////////
#include "TDataHora.h"
#include<iostream>
#include<sstream> // string stream

TDataHora::TDataHora(){}
TDataHora::TDataHora(int d, int m, int a, int h, int min, double s):TData(d,m,a),THora(h,min,s){}
TDataHora::TDataHora(const TData &d, const THora &t):TData(d),THora(t){}
TDataHora::TDataHora(const string &dt){ set(dt);}
TDataHora::TDataHora(const char *dt){ set(dt);}

void TDataHora::set(const string &dt){
	if (dt.compare("HOJE_AGORA")==0) *this=hoje_agora();
	else{
		string str;
		istringstream xx(dt);
		getline(xx, str, ' ');
		TData::set(str);
		str.erase();
		getline(xx, str);
		THora::set(str);
	}
}

bool TDataHora::set(int d, int m, int a, int h, int min, double s){
	bool res=TData::set(d,m,a);
	res=THora::set(h,min,s) && res;
	return res;
}

void TDataHora::setData(const TData &d){TData::operator=(d);}				
void TDataHora::setTempo(const THora &t){THora::operator=(t);}		

void TDataHora::operator=(const string &dt){ set(dt);}

TData TDataHora::getData() const{return TData(dia,mes,ano);}
THora TDataHora::getTempo() const{return THora(hora,minuto,segundo);}

string TDataHora::datahora_str() const{
	return data_str()+' '+tempo_str();
}

bool TDataHora::operator<(const TDataHora &outra) const{
	if (getData()==outra.getData()) return getTempo()<outra.getTempo();
	else return getData()<outra.getData();
}

THora TDataHora::operator-(const TDataHora &outra) const{
	if (outra>*this) return THora(0,0,0.0);
	else{
		THora dhoras((getData()-outra.getData())*24,0,0.0);
		if (getTempo()>=outra.getTempo()) return dhoras+(getTempo()-outra.getTempo());
		else return dhoras-(outra.getTempo()-getTempo());
	}
}

bool TDataHora::operator>(const TDataHora &outra) const{return outra<(*this);}
bool TDataHora::operator!=(const TDataHora &outra) const{return (*this)<outra||outra<(*this);}
bool TDataHora::operator==(const TDataHora &outra) const{return !((*this)!=outra);}
bool TDataHora::operator<=(const TDataHora &outra) const{return !((*this)>outra);}
bool TDataHora::operator>=(const TDataHora &outra) const{return !((*this)<outra);}

TDataHora TDataHora::hoje_agora(){
	TDataHora dt(TData::hoje(),THora::agora());
	return dt;
}

ostream &operator<<(ostream &os, const TDataHora &dt){
	os<<dt.datahora_str();
	return os;
}

istream &operator>>(istream &is, TDataHora &dt){
	string sd, st;
	is>>sd>>st;
	TData d(sd);
	THora t(st);
	dt.setData(sd);
	dt.setTempo(st);
	return is;
}

//Paulo Gouveia