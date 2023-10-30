#include "crow.h"
#include "accounting/Accounting.h"
#include "crow/middlewares/cors.h"

#include <mutex>
#include <unordered_set>

int main()
{
    crow::App<crow::CORSHandler> app;

    std::mutex mtx;;
    std::unordered_set<crow::websocket::connection*> users;

    auto accounting = std::make_shared<Accounting>();

    CROW_ROUTE(app, "/close")([accounting](){
        crow::response res(std::string(accounting->closeTab().dump()));
        res.add_header("Content-Type", "application/json");
        return res;
    });

    CROW_ROUTE(app, "/pay")([accounting](){
        crow::response res(std::string(accounting->pay(35, "cash").dump()));
        res.add_header("Content-Type", "application/json");
        return res;
    });

    CROW_ROUTE(app, "/reservation").methods("POST"_method)([](const crow::request& req){

        std:: cout << "Reservation Request: \n" + req.body << std::endl;

        crow::response res("{\"available\": \"yes\"}");
        res.add_header("Content-Type", "application/json");
        res.code = 200;
        
        return res;
    });

    CROW_ROUTE(app, "/ws")
        .websocket()
        .onopen([&](crow::websocket::connection& conn){
            CROW_LOG_INFO << "new websocket connection";
            std::lock_guard<std::mutex> _(mtx);
            users.insert(&conn);
            })

        .onclose([&](crow::websocket::connection& conn, const std::string& reason){
            CROW_LOG_INFO << "websocket connection closed: " << reason;
            std::lock_guard<std::mutex> _(mtx);
            users.erase(&conn);
            })

        .onerror([&](crow::websocket::connection& /*conn*/) {
            std::cout << "websocket error" << std::endl;
            CROW_LOG_INFO << "websocket error";
        })

        .onmessage([&](crow::websocket::connection& /*conn*/, const std::string& data, bool is_binary){
            std::lock_guard<std::mutex> _(mtx);
            for(auto u:users)
                if (is_binary)
                    u->send_binary(data);
                else
                    u->send_text(data);
            });

    app.port(8000).multithreaded().run();
}