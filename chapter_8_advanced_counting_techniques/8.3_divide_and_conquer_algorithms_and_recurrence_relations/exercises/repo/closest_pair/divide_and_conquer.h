/*
  Discrete Mathematics and Its Applications
  by Dr. Kenneth H. Rosen
  Chapter 8.3 Divide and Conquer Algorithms and Recurrence Relations
  Solution 24
  Rakesh Kumar, cpp.rakesh@gmail.com
  18/07/2018
*/

#ifndef DISCRETE_MATHEMATICS_AND_ITS_APPLICATIONS_CHAPTER_8_8_3_DIVIDE_AND_CONQUER_ALGORITHMS_AND_RECURRENCE_RELATIONS_EXERCISES_REPO_DIVIDE_AND_CONQUER_H_
#define DISCRETE_MATHEMATICS_AND_ITS_APPLICATIONS_CHAPTER_8_8_3_DIVIDE_AND_CONQUER_ALGORITHMS_AND_RECURRENCE_RELATIONS_EXERCISES_REPO_DIVIDE_AND_CONQUER_H_

#include "common.h"

const int inf = 1 << 30;

namespace discrete_mathematics {
    namespace chapter_8 {
        template <typename T>
        class DivideAndConquer {
        public:
            DivideAndConquer();
            ~DivideAndConquer();

            double closest(std::vector<std::pair<T, T>>& p);

        private:
            double m_closest(std::vector<std::pair<T, T>>& p, int s, int e);
            double m_strip(std::vector<std::pair<T, T>>& p);
        };
    };
};

template <typename T>
discrete_mathematics::chapter_8::DivideAndConquer<T>::DivideAndConquer() {}

template <typename T>
discrete_mathematics::chapter_8::DivideAndConquer<T>::~DivideAndConquer() {}

template <typename T>
double discrete_mathematics::chapter_8::DivideAndConquer<T>::closest(std::vector<std::pair<T, T>>& p) {
    // sort by x
    std::sort(p.begin(), p.end(), [](std::pair<T, T> a, std::pair<T, T> b) {
            return a.first < b.first;
        });
    return m_closest(p, 0, p.size() - 1);
}

template <typename T>
double discrete_mathematics::chapter_8::DivideAndConquer<T>::m_closest(std::vector<std::pair<T, T>>& p, int s, int e) {
    discrete_mathematics::chapter_8::Common<T> common;
    if (s < e) {
        if (s + 1 == e)
            return common.euclidean_distance(p[s], p[e]);
        const int m = (s + e) >> 1;
        const double l_min = m_closest(p, s, m);
        const double r_min = m_closest(p, m + 1, e);
        double min = std::min(l_min, r_min);

        std::vector<std::pair<T, T>> list;
        for (int i = s; i < m; ++i)
            if (std::abs(p[i].first - p[m].first) < min)
                list.push_back(p[i]);

        list.push_back(p[m]);

        for (int i = m + 1; i <= e; ++i)
            if (std::abs(p[i].first - p[m].first) < min)
                list.push_back(p[i]);

        if (list.size() < 2)
            return min;
        else
            return std::min(min, m_strip(list));
    }

    return inf;
}

template <typename T>
double discrete_mathematics::chapter_8::DivideAndConquer<T>::m_strip(std::vector<std::pair<T, T>>& p) {
    // sort by y
    discrete_mathematics::chapter_8::Common<T> common;
    std::sort(p.begin(), p.end(), [](std::pair<T, T> a, std::pair<T, T> b) {
            return a.second < b.second;
        });

    double min = common.euclidean_distance(p[0], p[1]);
    for (std::size_t i = 1; i < p.size() - 1; ++i)
        for (std::size_t j = i + 1; j < p.size() && (p[j].second - p[i].second) < min; ++j)
            min = std::min(min, common.euclidean_distance(p[i], p[j]));

    return min;
}

#endif // DISCRETE_MATHEMATICS_AND_ITS_APPLICATIONS_CHAPTER_8_8_3_DIVIDE_AND_CONQUER_ALGORITHMS_AND_RECURRENCE_RELATIONS_EXERCISES_REPO_DIVIDE_AND_CONQUER_H_
