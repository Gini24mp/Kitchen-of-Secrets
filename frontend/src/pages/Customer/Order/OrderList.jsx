import React, { useContext, useState } from 'react';

import { OrderContext } from './Order';

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

function OrderList({ socket }) {
  const [loading, setLoading] = useState(false);
  const { order, removeFromOrder } = useContext(OrderContext);

  const food = order.food;
  const beverages = order.beverages;

  const totalFoodPrice = food.reduce((total, item) => total + item.price, 0);
  const totalBeveragePrice = beverages.reduce(
    (total, item) => total + item.price,
    0
  );
  const totalPrice = totalFoodPrice + totalBeveragePrice;

  function handleOrderClick() {
    setLoading(true);

    if (socket) {
      socket.send(
        JSON.stringify({ type: 'make-order', data: { order, totalPrice } })
      );
    }
  }

  return (
    <Box
      sx={{
        p: 2,
        m: 2,
        width: '30%',
        border: '2px solid',
        borderRadius: '4px',
        borderColor: 'primary.main',
        backgroundColor: 'rgba(0, 0, 0, 0.7)',
        padding: '20px',
        borderRadius: '10px'
      }}
    >
      <Typography variant='h3' sx={{ m: 2 }}>
        Order
      </Typography>

      <Divider />

      <Box
        sx={{
          p: 2,
          mt: 2,
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
          <Typography variant='h6'>Food</Typography>
          {food.map((item, index) => (
            <ListItem key={index}>
              <ListItemText primary={`${item.name} - R${item.price}`} />
              <Button
                variant='outlined'
                onClick={() => removeFromOrder(index, 'food')}
              >
                Remove
              </Button>
            </ListItem>
          ))}

          <Typography variant='h6'>Beverages</Typography>
          {beverages.map((item, index) => (
            <ListItem key={index}>
              <ListItemText primary={`${item.name} - R${item.price}`} />
              <Button
                variant='outlined'
                onClick={() => removeFromOrder(index, 'beverage')}
              >
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
