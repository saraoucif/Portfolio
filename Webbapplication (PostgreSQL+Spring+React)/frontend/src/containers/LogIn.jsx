import React, {useState} from 'react';
import {Box, TextField, Button} from '@mui/material';
import LogInLogo from "../components/LogInLogo.jsx";
import {Typography} from "@material-ui/core";

function LogIn({onLogin}) {
    const [username, setUsername] = useState('');
    const [password, setPassword] = useState('');

    const handleSubmit = (event) => {
        event.preventDefault();
        onLogin();
    };

    return (
        <Box
            sx={{
                display: 'flex',
                alignItems: 'center',
                justifyContent: 'center',
                height: '100vh',
                width: '300vh',
                maxWidth: '200%',
                backgroundColor: '#E9EBEC',
            }}
        >
            <form onSubmit={handleSubmit}
                  style={{
                      position: 'absolute',
                      top: '50%',
                      left: '50%',
                      transform: 'translate(-50%, -50%)'
                  }}>
                <Box
                    sx={{
                        display: 'flex',
                        flexDirection: 'column',
                        alignItems: 'center',
                        backgroundColor: '#fff',
                        borderRadius: '1px',
                        border: 'solid 7px #334F68',
                        boxShadow: '0px 4px 10px rgba(0, 0, 0, 0.1)',
                        width: '1100px',
                        height: '525px',
                        maxWidth: '100%',
                        margin: 'auto',

                    }}
                >
                    <LogInLogo/>
                    <Box
                        sx={{
                            backgroundColor: '#E9EBEC',
                            display: 'flex',
                            flexDirection: 'column',
                            alignItems: 'center',
                            width: '450px',
                            height: '220px',
                        }}
                    >
                        <Typography
                            style={{
                                fontFamily: 'Montserrat',
                                fontWeight: 'bold',
                                fontSize: '15px',
                                color: '#DC823D',
                                alignSelf: 'flex-start', // align to left
                                paddingLeft: '65px',
                                marginTop: '30px',
                                marginBottom: '0px',
                            }}
                        >
                            Username
                        </Typography>

                        <TextField
                            variant="outlined"
                            size="small"
                            value={username}
                            onChange={(event) => setUsername(event.target.value)}

                            sx={{
                                '& input': {
                                    fontSize: '1.0rem',
                                    width: '300px'
                                },

                                backgroundColor: '#ffffff',
                            }}
                        />

                        <Typography
                            style={{
                                fontFamily: 'Montserrat',
                                fontWeight: 'bold',
                                fontSize: '15px',
                                color: '#DC823D',
                                alignSelf: 'flex-start',
                                paddingLeft: '65px',
                                marginTop: '10px',
                                marginBottom: '0px',
                            }}
                        >
                            Password
                        </Typography>

                        <TextField
                            variant="outlined"
                            size="small"
                            type="password"
                            value={password}
                            onChange={(event) => setPassword(event.target.value)}
                            sx={{
                                '& input': {
                                    fontSize: '1.0rem',
                                    width: '300px'
                                },

                                backgroundColor: '#ffffff',
                            }}
                        />

                        <Button
                            variant="text"
                            sx={{
                                fontFamily: 'Montserrat',
                                fontSize: '11px',
                                fontWeight: 'bold',
                                alignSelf: 'flex-start',
                                color: '#334F68',
                                textTransform: 'none',
                                paddingLeft: '65px',
                                marginTop: '2px',
                            }}
                        >
                            Forgot Password?
                        </Button>

                        <Button variant="contained" type="submit"
                                sx={{
                                    fontFamily: 'Montserrat',
                                    fontWeight: 'bold',
                                    fontSize: '12px',
                                    marginTop: '3rem',
                                    width: '110px',
                                    alignSelf: 'center',
                                    backgroundColor: '#DC823D'
                                }}>
                            Log In

                        </Button>
                    </Box>
                </Box>
            </form>
        </Box>
    );
}

export default LogIn;
