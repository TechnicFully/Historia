#pragma once

/***** USER-RELEVANT VARIABLES *****/
#define HISTORIA_VERSION 1.00
#define HISTORIA_VERSION_MAJOR 1
#define HISTORIA_VERSION_MINOR 0
#define HISTORIA_VERSION_PATCH 0
#define HISTORIA_VERSION_STRING "1.0.0"




#include <deque>
#include <limits>
#include <optional>
#include <cstdint>


#ifdef HISTORIA_DEBUG
#include <plog/Log.h>
#else
struct black_hole_t
{
    template <typename T> black_hole_t operator<<(T &&)
    {
        return {};
    }
};
#define PLOG_VERBOSE black_hole_t{}
#define PLOG_DEBUG black_hole_t{}
#define PLOG_ERROR black_hole_t{}
#endif


template <typename T>
class Historia
{
    private:
        //This class is for keeping track of our *current* index
        template <typename I>
        struct History_stack {
            std::deque<T> pages;
            I page_index = 0;

            static_assert(std::is_arithmetic<I>::value, "Not an arithmetic type");
            static_assert(std::numeric_limits<I>::min() >= 0, "Arithmetic type should have a minimum value of 0 (zero)");

            void push(T data) {
                if (pages.empty()) {
                    pages.push_back(data);
                    page_index = 0;
                } else {
                    pages.push_back(data);
                    increment_index();
                }
            }

            void increment_index() {
                if (page_index > pages.size()) {
                    page_index = pages.size();
                } else {
                    page_index++;
                }
            }

            I size() {
                return pages.size() - 1; //Account for alignment. A pages size of 1 will have an index of 0
            }

            I max_size() {
                return std::numeric_limits<I>::max();
            }
        };

        History_stack<uint16_t> history_stack; //Max of 65536 values


    public:
        // ██████╗ ██████╗ ███╗   ██╗███████╗████████╗██████╗ ██╗   ██╗ ██████╗████████╗ ██████╗ ██████╗ ███████╗
        //██╔════╝██╔═══██╗████╗  ██║██╔════╝╚══██╔══╝██╔══██╗██║   ██║██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗██╔════╝
        //██║     ██║   ██║██╔██╗ ██║███████╗   ██║   ██████╔╝██║   ██║██║        ██║   ██║   ██║██████╔╝███████╗
        //██║     ██║   ██║██║╚██╗██║╚════██║   ██║   ██╔══██╗██║   ██║██║        ██║   ██║   ██║██╔══██╗╚════██║
        //╚██████╗╚██████╔╝██║ ╚████║███████║   ██║   ██║  ██║╚██████╔╝╚██████╗   ██║   ╚██████╔╝██║  ██║███████║
        // ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝  ╚═════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚══════╝
        Historia(T const& data) {
            push(data);
        }

        Historia() {};


        // █████╗  ██████╗ ██████╗███████╗███████╗███████╗
        //██╔══██╗██╔════╝██╔════╝██╔════╝██╔════╝██╔════╝
        //███████║██║     ██║     █████╗  ███████╗███████╗
        //██╔══██║██║     ██║     ██╔══╝  ╚════██║╚════██║
        //██║  ██║╚██████╗╚██████╗███████╗███████║███████║
        //╚═╝  ╚═╝ ╚═════╝ ╚═════╝╚══════╝╚══════╝╚══════╝
        T next() {
            if (history_stack.page_index < history_stack.size()) {
                PLOG_VERBOSE << "Accessing next element " << history_stack.page_index << " " << history_stack.pages.size();
                history_stack.increment_index();
                return history_stack.pages.at(history_stack.page_index);
            }

            PLOG_DEBUG << "No next page";
            return history_stack.pages.at(history_stack.page_index);
        }

        T previous() {
            if (history_stack.page_index > 0) {
                PLOG_DEBUG << "Accessing previous element";
                history_stack.page_index--;
                return history_stack.pages.at(history_stack.page_index);
            }

            PLOG_DEBUG << "No previous page";
            return history_stack.pages.at(history_stack.page_index);
        }

        std::optional<T> current() {
            if (history_stack.pages.empty()) {
                return {};
            }

            return std::make_optional<T>(history_stack.pages.at(history_stack.page_index));
        }

        std::optional<T> first() {
          if (history_stack.pages.empty()) {
                return {};
            }

            return std::make_optional<T>(history_stack.pages.front());
        }

        std::optional<T> last() {
            if (history_stack.pages.empty()) {
                return {};
            }

            return std::make_optional<T>(history_stack.pages.back());
        }


        //███╗   ███╗ ██████╗ ██████╗ ██╗███████╗██╗███████╗██████╗ ███████╗
        //████╗ ████║██╔═══██╗██╔══██╗██║██╔════╝██║██╔════╝██╔══██╗██╔════╝
        //██╔████╔██║██║   ██║██║  ██║██║█████╗  ██║█████╗  ██████╔╝███████╗
        //██║╚██╔╝██║██║   ██║██║  ██║██║██╔══╝  ██║██╔══╝  ██╔══██╗╚════██║
        //██║ ╚═╝ ██║╚██████╔╝██████╔╝██║██║     ██║███████╗██║  ██║███████║
        //╚═╝     ╚═╝ ╚═════╝ ╚═════╝ ╚═╝╚═╝     ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝
        void push(T data) {
            //Check for duplicate data
            if (!history_stack.pages.empty()) {
                if (history_stack.pages.at(history_stack.page_index) == data) {
                    PLOG_DEBUG << "Trying to insert duplicate data. Returning...";
                    return;
                }
            }

            //Add new page after current index
            PLOG_VERBOSE << "Pushing data onto stack";
            history_stack.push(data);
        }

        // ██████╗ █████╗ ██████╗  █████╗  ██████╗██╗████████╗██╗   ██╗
        //██╔════╝██╔══██╗██╔══██╗██╔══██╗██╔════╝██║╚══██╔══╝╚██╗ ██╔╝
        //██║     ███████║██████╔╝███████║██║     ██║   ██║    ╚████╔╝ 
        //██║     ██╔══██║██╔═══╝ ██╔══██║██║     ██║   ██║     ╚██╔╝  
        //╚██████╗██║  ██║██║     ██║  ██║╚██████╗██║   ██║      ██║   
        // ╚═════╝╚═╝  ╚═╝╚═╝     ╚═╝  ╚═╝ ╚═════╝╚═╝   ╚═╝      ╚═╝   
        constexpr const auto max_size() noexcept {
            return history_stack.max_size();
        }

        auto size() noexcept {
            return history_stack.pages.size(); //noexcept since c++11
        }
};
