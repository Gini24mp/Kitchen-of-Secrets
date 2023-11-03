import React, { useState, useEffect } from 'react';

import {
  Box,
  Button,
  List,
  ListItem,
  Typography,
  ListItemText
} from '@mui/material';

function Reservations({ socket }) {
  const [reservations, setReservations] = useState([]);

  useEffect(() => {
    if (socket) {
      socket.addEventListener('message', addReservation);
    }

    return () => {
      if (socket) {
        socket.removeEventListener('message', addReservation);
      }
    };
  }, [socket]);

  const addReservation = (event) => {
    const { type, data } = JSON.parse(event.data);

    console.log('Oh No');

    if (type === 'make-res') {
      setReservations((prevReservations) => [...prevReservations, data]);
    }
  };

  function handleAccept(name) {
    setReservations((prevReservations) =>
      prevReservations.map((reservation) =>
        reservation.name === name
          ? { ...reservation, accepted: true }
          : reservation
      )
    );

    if (socket) {
      socket.send(
        JSON.stringify({ type: 'accept-res', data: { available: 'yes' } })
      );
    }
  }

  return (
    <Box
      sx={{
        display: 'flex',
        alignItems: 'center',
        flexDirection: 'column',
        justifyContent: 'center'
      }}
    >
      <Typography variant='h1' sx={{ m: 2 }}>
        Reservations
      </Typography>

      <List sx={{ p: 2 }}>
        {reservations.map((reservation, index) => (
          <ListItem
            key={index}
            sx={{
              m: 2,
              borderRadius: 2,
              border: '2px solid',
              borderColor: reservation.accepted ? 'grey' : 'primary.main'
            }}
          >
            <ListItemText
              primary={`${reservation.name} - ${reservation.seating} at ${reservation.time} for ${reservation.guests} guests`}
              secondary={reservation.accepted ? 'Accepted' : 'Pending'}
            />

            <Button
              variant='contained'
              disabled={reservation.accepted}
              onClick={() => handleAccept(reservation.name)}
            >
              {reservation.accepted ? 'Accepted' : 'Accept'}
            </Button>
          </ListItem>
        ))}
      </List>
    </Box>
  );
}

export default Reservations;
