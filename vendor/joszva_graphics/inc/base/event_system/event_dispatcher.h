#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include <functional>
#include <vector>

#include "event.h"

namespace joszva::graphics::priv
{
    /* singleton event dispatcher class that is designed specifically to handle any type of event */
    template<typename T>
    class event_dispatcher
    {
    private:
        /* event observer interface */
        using event_observer = std::function<void(const T& _event)>;

    public:
        static event_dispatcher* instance()
        {
            static event_dispatcher dispatcher;
            return &dispatcher;
        }

        void subscribe(event::event_type type, const event_observer& observer)
        {
            observers.push_back({type, observer});
        }

        void dispatch(const T& _event)
        {
            for (int i = 0; i < observers.size(); ++i)
            {
                if (observers[i].type == T::type())
                {
                    observers[i].observer(_event);
                }
            }
        }

    private:
        /* this acts as a map, maps an event type to an observer 
        when we push them back into our vector */
        struct subscribed_event
        {
            event::event_type type;
            event_observer observer;
        };

        std::vector<subscribed_event> observers;
    };
}
#endif