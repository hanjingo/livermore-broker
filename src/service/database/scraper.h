#ifndef SCRAPER_H
#define SCRAPER_H

#include <vector>

namespace database
{

class scraper
{
public:
    scraper()
    {}
    ~scraper()
    {}
    void connect(const char* ip, const uint16_t port, );
    void subscribe(std::vector<std::string>& topics);
    void unsubscribe(std::vector<std::string>& topics);

private:

};

}

#endif