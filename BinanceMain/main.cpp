#include "Application.hpp"

int main()
{
	Application app;
	app.Run();

	system("pause");
	
	return 0;
}
/*#include "binapi/api.hpp"
#include "binapi/websocket.hpp"

#include <boost/asio/io_context.hpp>
#include <boost/asio/steady_timer.hpp>

#include <sstream>
#include <string>
#include <jsoncpp/json/json.h>

#include <iostream>

using std::cout;
using std::endl;

int main() {
    boost::asio::io_context ioctx;

    binapi::ws::websockets ws{
         ioctx
        ,"stream.binance.com"
        ,"9443"
    };

    Json::Value root;
    Json::Reader reader;

    ws.diff_depth("ADAUSDT", binapi::e_freq::_100ms,
        [&root, &reader](const char* fl, int ec, std::string emsg, auto depths) {
            if (ec) {
                std::cerr << "subscribe diff_depth error: fl=" << fl << ", ec=" << ec << ", emsg=" << emsg << std::endl;

                return false;
            }
       
            std::ostringstream temp;
            temp << depths;
            std::string tempString = temp.str();
            bool parsingSuccessful = reader.parse(tempString, root);
            
            cout << "E: " << root["E"].asUInt64() << endl;
            cout << "s: " << root["s"].asString() << endl;
            cout << "u: " << root["u"].asUInt64() << endl;
            cout << "U: " << root["U"].asUInt64() << endl;
            cout << "a: " << root["a"][0][0].asString() << ", " << root["a"][0][1].asString() << endl;
            cout << "b: " << root["b"][0][0].asString() << ", " << root["b"][0][1].asString() << endl;
            std::cout << root["a"].size() << std::endl;
            //std::cout << "diff_depths: " << depths << std::endl;

            return true;
        }
    );


    boost::asio::steady_timer timer2{ ioctx, std::chrono::steady_clock::now() + std::chrono::seconds(15) };
    timer2.async_wait([&ws](const auto&) {
        std::cout << "async unsubscribing all" << std::endl;
        ws.async_unsubscribe_all();
        });

    ioctx.run();

    return EXIT_SUCCESS;
}*/
