#include <iostream>
#include <string>
#include <curl/curl.h>
#include <iostream>

using namespace std;


static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(void)
{
    CURL *curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.43.130:8080/gladiator/webapi/messages/111/34/128/163/211/"
                "195/done");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        cout << readBuffer <<endl;
        int inic=0;
        int leyendo = 0;

        int Stats[6];
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

        cout << "-------------------------" << endl << Stats[2]<<endl;
    }
    return 0;
}