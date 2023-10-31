import React, { useState } from 'react';
import {
  Box,
  List,
  Button,
  Divider,
  ListItem,
  Typography,
  ListItemText
} from '@mui/material';
import LoadingButton from '@mui/lab/LoadingButton';

function OrderList({ order, removeFromOrder }) {
  const [loading, setLoading] = useState(false);

  function handleOrderClick() {
    setLoading(true);
    console.log(order);
  }

  const totalPrice = order.reduce((total, item) => total + item.price, 0);

  return (
    <Box
      sx={{
        p: 2,
        m: 2,
        width: '30%',
        border: '2px solid',
        borderRadius: '4px',
        borderColor: 'primary.main'
      }}
    >
      <Typography variant='h3' sx={{ m: 2 }}>
        Order
      </Typography>

      <Divider />

      <Box
        sx={{
          p: 2,
          width: '100%',
          border: '2px solid',
          borderRadius: '4px',
          borderColor: 'primary.main'
        }}
      >
        <Typography variant='h4' sx={{ m: 2 }}>
          Items
        </Typography>

        <Divider />

        <List>
          {order.map((item, index) => (
            <ListItem key={index}>
              <ListItemText primary={`${item.name} - R${item.price}`} />
              <Button variant='outlined' onClick={() => removeFromOrder(index)}>
                Remove
              </Button>
            </ListItem>
          ))}
        </List>

        <Typography variant='h6' sx={{ m: 2 }}>
          Total: R{totalPrice}
        </Typography>
      </Box>

      <LoadingButton
        size='large'
        sx={{ m: 2 }}
        color='primary'
        loading={loading}
        variant='contained'
        onClick={handleOrderClick}
      >
        Order
      </LoadingButton>
    </Box>
  );
}

export default OrderList;
