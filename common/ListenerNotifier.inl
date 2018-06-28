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

#ifdef LISTENERNOTIFIER_H

namespace common
{

// -------------------------------------------------------------------------------------------------
template < class LISTENER_TYPE >
ListenerNotifier< LISTENER_TYPE >::ListenerNotifier( )
{
}

// -------------------------------------------------------------------------------------------------

template < class LISTENER_TYPE >
void
ListenerNotifier< LISTENER_TYPE >::add_listener( LISTENER_TYPE* listener )
{
    if ( !listener )
    {
        return;
    }

    m_listeners.locked( [listener]( ListenerMap& listeners )
    {
        auto it = listeners.find( listener );
        if ( it != listeners.end( ) )
        {
            return;
        }
        listeners[ listener ] = ListenerParameters( );
    } );
}

// -------------------------------------------------------------------------------------------------

template < class LISTENER_TYPE >
void
ListenerNotifier< LISTENER_TYPE >::remove_listener( LISTENER_TYPE* listener )
{
    if ( !listener )
    {
        return;
    }

    // Get removed signal for this listener
    auto signal = m_listeners.locked( [listener]( ListenerMap& listeners )
                                      -> std::shared_ptr< Signal >
    {
        auto it = listeners.find( listener );
        if ( it == listeners.end( ) )
        {
            return nullptr;
        }
        it->second.pending_for_remove = true;
        return it->second.free_to_remove_signal;
    } );
    if ( !signal )
    {
        return;
    }

    // Wait for the signal which notifies that all pending notifications using this listener
    // has been done.
    signal->wait( );

    // Now it is safe to remove the listener
    m_listeners.locked( [listener]( ListenerMap& listeners )
    {
        auto it = listeners.find( listener );
        if ( it == listeners.end( ) )
        {
            return false;
        }
        listeners.erase( it );
        return true;
    } );
}

// -------------------------------------------------------------------------------------------------

template < class LISTENER >
void
ListenerNotifier< LISTENER >::remove_all_listeners( )
{
    m_listeners.locked( []( ListenerMap& listeners )
    {
        listeners.clear( );
    } );
}

// -------------------------------------------------------------------------------------------------

template < class LISTENER_TYPE >
size_t
ListenerNotifier< LISTENER_TYPE >::get_listeners_count( ) const
{
    return m_listeners.locked( []( const ListenerMap& listeners )
    {
        return listeners.size( );
    } );
}

// -------------------------------------------------------------------------------------------------

template < class LISTENER_TYPE >
bool
ListenerNotifier< LISTENER_TYPE >::is_listener_added( LISTENER_TYPE* listener )
{
    bool added = m_listeners.locked( [&listener]( ListenerMap& listeners )
    {
        const auto it = listeners.find( listener );
        return it != listeners.cend( );
    } );
    return added;
}

// -------------------------------------------------------------------------------------------------

template < class LISTENER_TYPE >
bool
ListenerNotifier< LISTENER_TYPE >::is_listener_pending_for_remove( LISTENER_TYPE* listener )
{
    bool pending_for_remove = m_listeners.locked( [&listener]( ListenerMap& listeners )
    {
        const auto it = listeners.find( listener );
        return it != listeners.cend( ) && it->second.pending_for_remove;
    } );
    return pending_for_remove;
}

// -------------------------------------------------------------------------------------------------

template < class LISTENER_TYPE >
template < typename LISTENER_CALLBACK, typename... ARGS >
void
ListenerNotifier< LISTENER_TYPE >::notify_listeners( LISTENER_CALLBACK callback,
                                                     ARGS&&... args )
{
    // Select listeners for notification. The listeners which are under remove will be skipped.
    std::vector< LISTENER_TYPE* > listeners_to_notify;
    m_listeners.locked( [&listeners_to_notify]( ListenerMap& listeners )
    {
        for ( auto& item : listeners )
        {
            auto& params = item.second;

            // Skip items which are under remove
            if ( params.pending_for_remove )
            {
                continue;
            }

             // Cannot remove listener during notification
            ++params.pending_notification_counter;
            params.free_to_remove_signal->reset( );
            listeners_to_notify.push_back( item.first );
        }
    } );

    // Call listener call for each listener
    for( auto& listener : listeners_to_notify )
    {
        ( listener->*callback )( std::forward< ARGS >( args )... );
    }

    // Decrease notification counter and set removing signal if possible
    m_listeners.locked( [&listeners_to_notify]( ListenerMap& listeners )
    {
        for( auto& listener : listeners_to_notify )
        {
            auto it = listeners.find( listener );
            if ( it == listeners.end( ) )
            {
                continue;
            }
            auto& params = it->second;

            --params.pending_notification_counter;

            // Always the "last" notifier sets the signal
            if ( params.pending_notification_counter == 0 )
            {
                params.free_to_remove_signal->set( );
            }
        }
    } );
}

}  // common

#endif
