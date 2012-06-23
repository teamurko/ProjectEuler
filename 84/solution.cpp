#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <utility>
#include <cassert>
#include <numeric>

#include <boost/lexical_cast.hpp>
using namespace std;

#define REQUIRE(cond, message) \
    do { \
        if (!(cond)) { \
            std::cerr << message << std::endl; \
            assert(false); \
        } \
    } while (false)


typedef vector<size_t> DiceSize;

const size_t FIELD_SIZE = 40;
const size_t DIE_SIZE = 4;
const size_t NUM_DOUBLES = 3;

enum class
SquareType {GO, A1, CC1, A2, T1, R1, B1, CH1, B2, B3, JAIL, C1, U1, C2, C3,
            R2, D1, CC2, D2, D3, FP, E1, CH2, E2, E3, R3, F1, F2, U2, F3,
            G2J, G1, G2, CC3, G3, R4, CH3, H1, T2, H2};

namespace std {
    template <>
    class hash<SquareType>
    {
        public:
        size_t operator()( const SquareType& e ) const
        {
            return static_cast<size_t>(e);
        }
    };
};

typedef vector<vector<double>> GameState;
typedef unordered_map<SquareType, double> Transition;
typedef unordered_map<SquareType, Transition> Transitions;

void checkProbability(double value)
{
    REQUIRE(0.0 <= value && value <= 1.0,
            "Probability should be within [0,1]");
}

pair<
    vector<pair<size_t, double>>,
    vector<pair<size_t, double>>> distribution(const DiceSize& sizes)
{
    REQUIRE(sizes.size() == 2, "Only two dice are supported");
    unordered_map<size_t, double> result;
    vector<pair<size_t, double> > doubles;
    for (size_t i = 1; i <= sizes[0]; ++i) {
        for (size_t j = 1; j <= sizes[1]; ++j) {
            if (i == j) {
                doubles.push_back(make_pair(i + j, 1.0));
            } else {
                result[i + j] += 1.0;
            }
        }
    }
    for (auto& pr : result) {
        pr.second /= sizes[0] * sizes[1];
    }
    for (auto& pr : doubles) {
        pr.second /= sizes[0] * sizes[1];
    }
    return make_pair(
                vector<pair<size_t, double>>(result.begin(), result.end()),
                doubles);
}

SquareType move(SquareType square)
{
    size_t position = static_cast<size_t>(square);
    return static_cast<SquareType>((position + 1) % FIELD_SIZE);
}

SquareType move(SquareType square, size_t count)
{
    for (size_t i = 0; i < count; ++i) {
        square = move(square);
    }
    return square;
}

SquareType nextRailwayStation(SquareType square)
{
    square = move(square);
    while (square != SquareType::R1 && square != SquareType::R2 &&
           square != SquareType::R3 && square != SquareType::R4) {
        square = move(square);
    }
    return square;
}

SquareType nextUtilityCompany(SquareType square)
{
    square = move(square);
    while (square != SquareType::U1 && square != SquareType::U2) {
        square = move(square);
    }
    return square;
}

Transition transition(SquareType square)
{
    decltype(transition(square)) result;
    if (square == SquareType::CC1 || square == SquareType::CC2 ||
                    square == SquareType::CC3) {
        result[SquareType::GO] = 1.0;
        result[SquareType::JAIL] = 1.0;
        result[square] = 14.0;
    }
    else if (square == SquareType::CH1 || square == SquareType::CH2 ||
             square == SquareType::CH3) {
        result[SquareType::GO] = 1.0;
        result[SquareType::JAIL] = 1.0;
        result[SquareType::C1] = 1.0;
        result[SquareType::E3] = 1.0;
        result[SquareType::H2] = 1.0;
        result[SquareType::R1] = 1.0;
        result[nextRailwayStation(square)] += 2.0;
        result[nextUtilityCompany(square)] += 1.0;
        result[move(square, FIELD_SIZE - 3)] += 1.0;
        result[square] = 6.0;
    }
    for (auto& pr : result) {
        pr.second /= 16.0;
    }
    if (result.empty()) {
        if (square == SquareType::G2J) {
            result[SquareType::JAIL] = 1.0;
        } else {
            result[square] = 1.0;
        }
    }
    return result;
}

Transitions buildTransitions()
{
    Transitions result;
    for (size_t i = 0; i < FIELD_SIZE; ++i) {
        SquareType square = static_cast<SquareType>(i);
        result[square] = transition(square);
    }
    return result;
}

GameState next(const GameState& state)
{
    static const Transitions transitions = buildTransitions();
    static const auto pointsPair = distribution(DiceSize(2, DIE_SIZE));

    REQUIRE(state.size() == NUM_DOUBLES, "Game should have "
            << NUM_DOUBLES << " elements, but "
            << state.size() << " has.");
    REQUIRE(state.back().size() == FIELD_SIZE,
            "Game should have " << FIELD_SIZE << " squares, but "
            << state.back().size() << " has.");
    for (const auto& value : state) {
        REQUIRE(value.size() == state.back().size(), "All fields should have "
                << "equal number of squares.");
    }
    GameState result(state.size(), vector<double>(state.back().size()));
    for (size_t numDoubles = 0; numDoubles < NUM_DOUBLES; ++numDoubles) {
        const vector<double>& field = state[numDoubles];
        for (size_t index = 0; index < field.size(); ++index) {
            if (state[numDoubles][index] == 0.0) continue;

            SquareType start = static_cast<SquareType>(index);
            const auto& usualPoints = pointsPair.first;
            const auto& doublePoints = pointsPair.second;
            const double startProbability = state[numDoubles][index];

            for (const pair<size_t, double>& step : usualPoints) {
                SquareType firstLevel = move(start, step.first);
                const double firstLevelP = startProbability * step.second;
                const Transition& firstTransition =
                                                transitions.at(firstLevel);
                for (const auto& bonusStep : firstTransition) {
                    const double secondLevelP =
                                            bonusStep.second * firstLevelP;
                    // WTF?! Why not to go sometimes to cc3 after ch3?
                    /*
                    const Transition& secondTransition =
                                            transitions.at(bonusStep.first);
                    for (const auto& secondStep : secondTransition) {
                        const size_t squareId =
                                    static_cast<size_t>(secondStep.first);
                        REQUIRE(secondStep.first != SquareType::G2J,
                                "End in go to jail square");
                        result[0][squareId] += secondStep.second *
                                                    secondLevelP;
                    }
                    */
                    result[0][static_cast<size_t>(bonusStep.first)] +=
                                                secondLevelP;
                }
            }

            for (const pair<size_t, double>& step : doublePoints) {
                if (numDoubles + 1 == NUM_DOUBLES) {
                    const double endProbability =
                                            startProbability * step.second;
                    static size_t jailIndex =
                                        static_cast<size_t>(SquareType::JAIL);
                    result[0][jailIndex] += endProbability;
                } else {
                    SquareType firstLevel = move(start, step.first);
                    const double firstLevelP = startProbability * step.second;
                    const Transition& firstTransition =
                                                transitions.at(firstLevel);
                    for (const auto& bonusStep : firstTransition) {
                        const double secondLevelP =
                                            bonusStep.second * firstLevelP;
                        // WTF?! Why not to go sometimes to cc3 after ch3?
                        /*
                        const Transition& secondTransition =
                                            transitions.at(bonusStep.first);
                        for (const auto& secondStep : secondTransition) {
                            const size_t squareId =
                                    static_cast<size_t>(secondStep.first);
                            REQUIRE(secondStep.first != SquareType::G2J,
                                    "End in go to jail square");
                            result[numDoubles + 1][squareId] +=
                                        secondStep.second * secondLevelP;
                        }
                        */
                        result[numDoubles + 1][static_cast<size_t>(bonusStep.first)] +=
                                                secondLevelP;
                    }
                }
            }
        }
    }
    return result;
}

void solve(size_t numIterations)
{
    GameState state(NUM_DOUBLES, vector<double>(FIELD_SIZE));
    state[0][0] = 1.0;
    for (size_t it = 0; it < numIterations; ++it) {
        state = next(state);
    }
    vector<double> ans(FIELD_SIZE);
    for (size_t numDoubles = 0; numDoubles < NUM_DOUBLES; ++numDoubles) {
        for (size_t index = 0; index < FIELD_SIZE; ++index) {
            ans[index] += state[numDoubles][index];
        }
    }
    cout.precision(10);
    cout << fixed;
    double sum = 0.0;
    vector<pair<double, size_t> > res;
    for (size_t index = 0; index < FIELD_SIZE; ++index) {
        res.push_back(make_pair(ans[index], index));
        sum += ans[index];
    }
    cerr << sum << endl;
    sort(res.begin(), res.end());
    reverse(res.begin(), res.end());
    for (const auto& pr : res) {
        cout << pr.first << " " << pr.second << endl;
    }
}

void printUsage(const char* name)
{
    cerr << "Usage : " << name << " num_iterations" << endl;
}

int main(int argc, char* argv[])
{
    ios_base::sync_with_stdio(false);
    if (argc != 2) {
        printUsage(argv[0]);
        return 0;
    }
    solve(boost::lexical_cast<size_t>(argv[1]));
    return 0;
}
