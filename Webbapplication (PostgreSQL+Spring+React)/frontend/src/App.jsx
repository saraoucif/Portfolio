import Header from './components/Header';
import Body from "./components/Body";
import Box from "@mui/material/Box";

function App() {
    return (
        <Box
            sx={{
                backgroundColor: '#E9EBEC',
                width: '100vw',
                height: '116vh',
                overflowX: 'hidden',
            }}>
            <Header/>
            <Body/>
        </Box>
    );
}

export default App;

