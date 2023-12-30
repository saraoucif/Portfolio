import Box from "@mui/material/Box";
import logo from "/Users/joannaxu/Desktop/SAGA-KTH/saga-app/src/assets/Logo_softhouse_original_new.png";
//import logo from "C:\\Users\\Olivia Burgess\\Desktop\\saga-frontend\\saga-app\\src\\Logo_softhouse_original_new.png";

export default function Logo() {
    return (
        <Box
            component="img"
            sx={{
                height: 70,
                width: 180,
                maxHeight: {xs: 233, md: 167},
                maxWidth: {xs: 350, md: 250},
                marginLeft: '-10px'
            }}
            alt="logo"
            src={logo}/>
    );
}
