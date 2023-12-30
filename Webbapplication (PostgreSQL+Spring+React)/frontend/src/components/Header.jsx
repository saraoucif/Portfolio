import React from 'react';
import UserAvatar from './UserAvatar';
import Box from "@mui/material/Box";
import {Grid} from "@mui/material";
import Logo from "./Logo";

function Header() {
    return (
        <Grid container rowSpacing={10}
              sx={{
                  backgroundColor: '#E9EBEC',
                  marginX: 5,
                  paddingY: '5px',
              }}>
            <Grid item xs={12}>
                <Box
                    sx={{
                        backgroundColor: '#E9EBEC',
                        color: '#000000',
                        marginX: 0,
                        padding: '10px',
                        marginY: '10px',
                        display: 'flex',
                        flexDirection: 'row',
                        alignItems: 'center',
                        justifyContent: 'space-between',
                        width: '94.5%',
                        height: 25,
                    }}
                >
                    <Logo/>
                    <UserAvatar/>
                </Box>

            </Grid>
        </Grid>
    );
}

export default Header;
