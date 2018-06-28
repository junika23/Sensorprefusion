/*
// -------------------------------------------------------------------------------------------------
//
// Copyright (C) Juniarto Saputra (juniarto.wongso@gmail.com). All rights reserved.
//
// This software, including documentation, is protected by copyright controlled by
// the contributor(s). All rights are reserved. Copying, including reproducing, storing,
// adapting or translating, any or all of this material requires the prior written
// consent of the contributor(s).
//
// -------------------------------------------------------------------------------------------------
*/

#ifndef LISTENERNOTIFIER_H
#define LISTENERNOTIFIER_H

#include <cstdint>
#include <map>
#include <memory>
#include <vector>

#include "Atomic.h"
#include "Signal.h"

namespace common
{

template< class LISTENER_TYPE >
class ListenerNotifier
{
public:

    ListenerNotifier( );
    virtual ~ListenerNotifier( ) = default;

    /**
     * Adds a listener.
     * @note Note that this call MUST NOT be called in a listener event otherwise it causes
     * dead lock.
     * @param listener is a pointer to derived ServiceListenerBase object
     */
    virtual void add_listener( LISTENER_TYPE* listener );

    /**
     * Removes a listener.
     * @note Note that this call MUST NOT be called in a listener event otherwise it causes
     * dead lock.
     * @param listener is a pointer to derived ServiceListenerBase object
     */
    virtual void remove_listener( LISTENER_TYPE* listener );

    /**
     * Gets the number of listeners.
     * @return The number of listeners.
     */
    size_t get_listeners_count( ) const;

    /**
     * Indicates whether the listener is already added or not.
     * @return True if the listener has been already added otherwise false.
     */
    bool is_listener_added( LISTENER_TYPE* listener );

    /**
     * Indicates whether the listener is currently pending for remove or not.
     * @return True if the listener is pending for remove otherwise false.
     */
    bool is_listener_pending_for_remove( LISTENER_TYPE* listener );

protected:

    /**
     * Removes all listeners.
     * @deprecated This method will be removed in the future, the removes should be executed
     * properly to avoid shared responsibilies.
     */
    void remove_all_listeners( );

    /**
     * Notifies the given callback (with arguments) of all listeners.
     */
    template< typename LISTENER_CALLBACK, typename... ARGS >
    void notify_listeners( LISTENER_CALLBACK callback, ARGS&& ... args );

private:

    /**
     * Parameters of listener objects.
     */
    struct ListenerParameters
    {
        uint32_t pending_notification_counter;
        bool pending_for_remove;
        std::shared_ptr< Signal > free_to_remove_signal;

        ListenerParameters( )
            : pending_notification_counter( 0 )
            , pending_for_remove( false )
            , free_to_remove_signal( std::make_shared< Signal >( ) )
        {
            free_to_remove_signal->set( );
        }
    };
    using ListenerMap = std::map< LISTENER_TYPE*, ListenerParameters >;

    /**
     * The list of listeners.
     */
    Atomic< ListenerMap > m_listeners;
};

} // common

#include "ListenerNotifier.inl"

#endif // LISTENERNOTIFIER_H
