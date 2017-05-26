//
// Created by gerardo on 20/05/17.
//

#ifndef GLADIATOR_PETICIONES_H
#define GLADIATOR_PETICIONES_H

#include <iostream>
#include <iomanip>
#include <curl/curl.h>
#include <locale>
#include <sstream>
#include <string>

using namespace std;

string itos ( int Number )
{
    stringstream ss;
    ss << Number;
    return ss.str();
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void Solicita(int Stats[]){
    {
        CURL *curl;
        CURLcode res;
        string readBuffer;
        string URL= "http://192.168.43.130:8080/gladiator/webapi/messages/";
        for (int i = 0; i < 6; ++i) {
            URL.append(itos(Stats[i]));
            URL.append("/");
        }

        URL.append("done");
        curl = curl_easy_init();
        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
            //http://192.168.43.130:8080/gladiator/webapi/messages/111/34/128/163/211/195/done
            //curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.43.130:8080/gladiator/webapi/messages/20/20/20/20/20/20/done");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            //Parsear el JSON
            int inic=0;
            int leyendo = 0;
            int ind=0;
            for(int i=0; i<(readBuffer.length()-1);i++) {

                if(readBuffer[i] == ':' && leyendo==0){
                    inic = i+1;
                    leyendo=1;
                }
                if (readBuffer[i] == ',' || readBuffer[i] == '}' && leyendo==1){
                    string temp = readBuffer.substr(inic,i-inic);
                    Stats[ind] = stoi(temp);
                    ind++;
                    cout << readBuffer.substr(inic,i-inic) << endl;
                    leyendo=0;
                }
            }
        }
    }
}


#endif //GLADIATOR_PETICIONES_H
