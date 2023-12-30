import * as React from 'react';
import Box from '@mui/material/Box';
import Stepper from '@mui/material/Stepper';
import Step from '@mui/material/Step';
import StepLabel from '@mui/material/StepLabel';
import StepIcon from '@mui/material/StepIcon';
import CheckCircle from '@mui/icons-material/CheckCircle';
import {StepConnector} from "@mui/material";
import {useEffect} from "react";

function CustomConnector() {
    return (
        <StepConnector
            sx={{
                '& .MuiStepConnector-line': {
                    borderColor: 'red',
                    borderWidth: 2,
                    borderStyle: 'solid',
                    flexGrow: '1 !important',
                },
            }}
        />
    );
}

const CustomStepIcon = (props) => {
    const {active, completed} = props;

    if (active || completed) {
        return (
            <CheckCircle sx={{
                color: '#DC823D',
                fontSize: '23px'
            }}/>
        );
    } else {
        return (
            <StepIcon {...props} />
        );
    }
}

const steps = ['Start', 'Commit', 'Go Live', 'Close'];

export default function Milestones(data) {

    const editable = data.editableMilestones;
    const [activeStep, setActiveStep] = React.useState(-1);

    useEffect(() => {
        if (data.milestones != null) {
            if (data.milestones.milestone4) setActiveStep(4);
            else if (data.milestones.milestone3) setActiveStep(2);
            else if (data.milestones.milestone2) setActiveStep(1);
            else if (data.milestones.milestone1) setActiveStep(0);
            else setActiveStep(-1);
        }
    }, [data]);

    const handleStepClick = (index) => {
        if (editable) {
            setActiveStep((prevActiveStep) => {
                let newActiveStep;
                if (index === prevActiveStep) newActiveStep = prevActiveStep - 1;
                else if (index === 3) newActiveStep = 4;
                else newActiveStep = index;

                const newData = {
                    ...data,
                    milestones: {
                        milestone1: newActiveStep >= 0,
                        milestone2: newActiveStep >= 1,
                        milestone3: newActiveStep >= 2,
                        milestone4: newActiveStep === 4,
                    },
                };

                data.onDataUpdate(newData.milestones);
                return newActiveStep;
            });
        }
    };


    return (
        <Box sx={{width: '100%'}}>
            <Stepper activeStep={activeStep} connector={<CustomConnector/>}>
                {steps.map((label, index) => {
                    const stepProps = {};
                    const labelProps = {};

                    return (
                        <Step key={label}
                              onClick={() => handleStepClick(index)}
                              {...stepProps} >
                            <StepLabel sx={{
                                flexDirection: 'column',
                                '& .MuiStepLabel-label': {
                                    fontFamily: 'Montserrat',
                                    fontSize: '10px',
                                    color: '#333',
                                },
                                /* milestones cirklarna */
                                '.css-1u4zpwo-MuiSvgIcon-root-MuiStepIcon-root': {
                                    color: index <= activeStep ? '#DC823D !important' : '#E9EBEC !important',
                                    border: '0px solid #DC823D !important',
                                    borderRadius: 5
                                },
                                '.css-117w1su-MuiStepIcon-text': {
                                    display: 'none'
                                },
                                '.css-1u4zpwo-MuiSvgIcon-root-MuiStepIcon-root.Mui-completed': {},
                                '.MuiStepIcon-active:not(.MuiStepIcon-completed) > .MuiStepIcon-text': {
                                    display: 'none'
                                },

                            }}{...labelProps}
                                       StepIconComponent={CustomStepIcon}
                            >{label}</StepLabel>
                        </Step>
                    );
                })}
            </Stepper>

            <Box sx={{display: 'flex', flexDirection: 'row', pt: 2}}>

                <Box sx={{flex: '1 1 auto'}}/>
            </Box>

        </Box>
    );
}

