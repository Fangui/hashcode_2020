#include "utils.hh"

float compute_score(std::vector<EndPoint> endpoints)
{
    float sum = 0.f;
    float div = 0.f;

//#pragma omp paralell for schedule (dynamic) reduction(+:sum)
    for (auto it = endpoints.begin(); it != endpoints.end(); ++it)
    {
        for (const auto &connection : conections)
        {
            for (const auto &video : videos)
            {
                if (endpoints.find(video.connection) == endpoints.end())
                    continue;

                sum += it->latency - connection.lenty;
            }
        }
    }

    for (const auto req : requests)
        div += req.second;

    return sum / div;
}
