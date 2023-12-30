import * as React from 'react';
import Avatar from '@mui/material/Avatar';
import Stack from '@mui/material/Stack';
import Box from "@mui/material/Box";
import {Typography} from "@mui/material";

export default function UserAvatar() {
    return (
        <Stack direction="row" spacing={2}>
            <Box sx={{display: 'inline-flex', alignItems: 'center'}}>
                <Typography variant="string"
                            sx={{
                                fontFamily: 'Montserrat',
                                fontSize: 14,
                                fontWeight: 'bold',
                                padding: 0,
                                color: '#334F68',
                                height: 19
                            }}
                >Name Namesson</Typography>
                <Avatar
                    sx={{
                        bgcolor: '#E9EBEC',
                        height: 40,
                        width: 40,
                    }}
                />
            </Box>
        </Stack>
    );
}
