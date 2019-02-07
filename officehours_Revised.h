#ifndef OFFICEHOURS_REVISED_H
#define OFFICEHOURS_REVISED_H
#include <cstdlib>

class bool_source
{
public:
    bool_source(double p);
    bool query( ) const;
private:
    double probability;
};

class averager
{
public:
    averager( );
    void next_number(double value);
    std::size_t how_many_numbers( ) const { return count; }
    double average( ) const;
private:
    std::size_t count; // How many numbers have been given to the averager
    double sum;   // Sum of all the numbers given to the averager
};

class officehours
{
public:
    officehours();
    void one_second( );
    void start(int next);
    bool is_busy( ) const { return (meet_time_left > 0); }
private:
    unsigned int seconds_for_meeting; // Seconds for a meeting wash
    unsigned int meet_time_left;   // Seconds until washer no longer busy
};


#endif //OFFICEHOURS_REVISED_H
