
#include "searches.hpp"

std::pair<line_number, steps> barrierSearch(std::vector<AutoDocs>& docs, std::size_t request)
{
    std::size_t sz{ docs.size() };
    if (sz == 0)
    {
        return {-1, -1};
    }

    docs.push_back(AutoDocs{ docs.front() });
    AutoDocs& barrier{ docs.back() };
    barrier.setRequest(request); // make sure, that element exist

    std::size_t cmps{ 1 };
    std::size_t i{};
    for (; !docs[i].contains(request); ++i, ++cmps) {}
    
    if (i != sz)
    {   
        return { docs[i].getID(), cmps }; // element is found
    } 
    return { -1, -1 }; // element is not fount
}

std::size_t binarySearch
(std::vector<AutoDocs>& docs, int left, int right, std::size_t request, steps& step)
{
    if (left <= right)
    {
        int mid{ left + (right - left)/2 };
        if (docs[mid].contains(request)) 
        {
            return ++step, mid;
        }
        else if (docs[mid].getRequest() > request)
        {
            return ++step, binarySearch(docs, left, mid - 1, request, step);
        }
        return ++step, binarySearch(docs, mid + 1, right, request, step);
    }

    return -1; 
}

std::pair<line_number, steps> binarySearch(std::vector<AutoDocs>& docs, std::size_t request)
{
    steps step{};
    std::size_t i{ binarySearch(docs, 0, docs.size() - 1, request, step)  };

    if (i == std::numeric_limits<std::size_t>::max())
    {
        return { -1, -1 };
    } 
    return { docs[i].getID(), step };
}
