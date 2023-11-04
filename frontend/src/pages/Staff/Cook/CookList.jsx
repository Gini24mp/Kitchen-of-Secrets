import React from 'react';

import CookCard from './CookCard';

import { Box, Typography } from '@mui/material';

function CookList({ orders, selectOrder }) {
  return (
    <Box
      sx={{
        m: 2,
        p: 2,
        width: '60%',
        border: '4px solid',
        borderRadius: '4px',
        borderColor: 'primary.main'
      }}
    >
      <Typography variant='h4'>New Orders</Typography>

      <Box sx={{ display: 'flex', overflow: 'scroll' }}>
        {orders.map((order, index) => (
          <CookCard key={index} order={order} selectOrder={selectOrder} />
        ))}
      </Box>
    </Box>
  );
}

export default CookList;