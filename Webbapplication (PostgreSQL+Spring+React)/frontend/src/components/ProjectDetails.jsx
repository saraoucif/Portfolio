import * as React from 'react';
import Box from "@mui/material/Box";
import Grid from "@mui/material/Unstable_Grid2";
import TextField from "@mui/material/TextField";
import {Typography} from "@mui/material";
import {useEffect, useState} from "react";
import axios from "axios";
import Button from "@mui/material/Button";
import Milestones from "./Milestones.jsx";

function ProjectDetails(props) {
    let {selectedData} = props;
    const [saveClicked, setSaveClicked] = useState(false);
    const [editable, setEditable] = useState(false);

    const [description, setDescription] = useState('');
    const [notes, setNotes] = useState('');
    const [clientInformation, setClientInformation] = useState('');
    const [milestoneData, setMilestoneData] = useState([]);

    const [originalDescription, setOriginalDescription] = useState('');
    const [originalNotes, setOriginalNotes] = useState('');
    const [originalClientInformation, setOriginalClientInformation] = useState('');
    const [originalMilestoneData, setOriginalMilestoneData] = useState([]);

    const handleDataUpdate = (newMilestones) => {
        selectedData.milestone1 = newMilestones.milestone1;
        selectedData.milestone2 = newMilestones.milestone2;
        selectedData.milestone3 = newMilestones.milestone3;
        selectedData.milestone4 = newMilestones.milestone4;
        setMilestoneData(newMilestones);
    };

    const fetchProjectData = () => {
        if (selectedData != null) {
            axios.get("http://35.222.169.45:8080/api/v1/project/" + selectedData.id)
                .then((data) => {
                    setDescription(data.data.description)
                    setNotes(data.data.notes)
                    setClientInformation(data.data.clientInformation)
                    setMilestoneData({
                        milestone1: data.data.milestone1,
                        milestone2: data.data.milestone2,
                        milestone3: data.data.milestone3,
                        milestone4: data.data.milestone4
                    })

                    setOriginalNotes(data.data.notes);
                    setOriginalDescription(data.data.description);
                    setOriginalClientInformation(data.data.clientInformation);
                    setOriginalMilestoneData({
                        milestone1: data.data.milestone1,
                        milestone2: data.data.milestone2,
                        milestone3: data.data.milestone3,
                        milestone4: data.data.milestone4
                    })
                })
                .catch(error => console.log(error))
        }
    }

    useEffect(() => {
        setEditable(false);
        fetchProjectData()
    }, [selectedData])

    const handleDescriptionChange = (event) => {
        setDescription(event.target.value);
    };
    const handleNotesChange = (event) => {
        setNotes(event.target.value);
    };
    const handleClientInfoChange = (event) => {
        setClientInformation(event.target.value);
    };

    const handleEditClick = () => {
        //if user pressed cancel...restore fields to their original state
        if (editable) {
            setNotes(originalNotes);
            setDescription(originalDescription);
            setClientInformation(originalClientInformation);
            handleDataUpdate(originalMilestoneData)
        }
        setEditable(!editable);
        setSaveClicked(false);
    };

    const handleSaveClick = () => {
        setEditable(false);
        setSaveClicked(true);
        saveProjectDetailsToServer(description, notes, clientInformation, milestoneData);
        props.onDataUpdate(selectedData);
    };

    const saveProjectDetailsToServer = (description, notes, clientInformation, milestoneData) => {
        const url = "http://35.222.169.45:8080/api/v1/project/" + selectedData.id;
        selectedData.description = description;
        selectedData.notes = notes;
        selectedData.clientInformation = clientInformation;
        selectedData.milestone1 = milestoneData.milestone1;
        selectedData.milestone2 = milestoneData.milestone2;
        selectedData.milestone3 = milestoneData.milestone3;
        selectedData.milestone4 = milestoneData.milestone4;

        axios.put(url, selectedData, {
            headers: {
                "Content-Type": "application/json",
            },
        }).then(response => {
            console.log(response.data);
        })
            .catch(error => {
                console.log(error);
            });
    };

    return (
        <>
            <Box
                sx={{
                    backgroundColor: '#F2F2F2',
                    color: '#000000',
                    fontFamily: 'Montserrat',
                    fontWeight: 'bold',
                    fontSize: 8,
                    width: 430,
                    height: 724,
                    border: 1,
                    borderColor: 'rgba(126, 126, 126, 0.1)',
                    boxShadow: '0px 1px 1px rgba(0, 0, 0, 0.10) !important'

                }}>

                <Typography sx={{
                    fontFamily: 'Montserrat',
                    fontSize: 17,
                    fontWeight: 'bold',
                    mb: 1,
                    color: '#334F68',
                    padding: 2.5,
                    marginLeft: '2px',
                    marginTop: '5px',
                    height: '21px'

                }}> {selectedData ? selectedData.projectName : ''} </Typography>

                <Box
                    sx={{
                        height: 651,
                        width: '100%',
                        backgroundColor: '#FBFBFB',
                        color: '#000000',
                        fontFamily: 'Montserrat',
                        fontWeight: 'normal',
                        fontSize: 8,
                        borderTop: 0,
                        borderColor: '#8E8E8E',
                        boxShadow: '0px 2px 1px rgba(0, 0, 0, 0.25)'
                    }}>
                    {selectedData ? (
                        <Box sx={{flexGrow: 1, padding: '10px'}}>
                            <Grid container spacing={2}
                                  sx={{padding: 2}}>
                                <Grid xs={12} style={{padding: '16px'}}>
                                    <Milestones milestones={selectedData} editableMilestones={editable}
                                                saveClicked={saveClicked} onDataUpdate={handleDataUpdate}/>
                                </Grid>
                                <Grid xs={12}>
                                    <Typography sx={{
                                        fontFamily: 'Montserrat',
                                        fontSize: 13,
                                        fontWeight: 'bold',
                                        mb: 1,
                                        color: '#334F68'
                                    }}>Description</Typography>
                                    <TextField id="outlined-multiline-static"
                                               rows={4}
                                               multiline
                                               value={description}
                                               onChange={handleDescriptionChange}
                                               disabled={!editable}
                                               InputProps={{
                                                   style: {
                                                       color: 'black',
                                                       fontFamily: 'Montserrat',
                                                       fontSize: 13,
                                                       width: '380px'
                                                   }
                                               }}
                                               placeholder={'Write a description...'}
                                    />
                                </Grid>
                                <Grid xs={12}>
                                    <Typography sx={{
                                        fontFamily: 'Montserrat',
                                        fontSize: 13,
                                        fontWeight: 'bold',
                                        mb: 1,
                                        color: '#334F68'
                                    }}>Notes</Typography>
                                    <TextField id="outlined-multiline-static"
                                               rows={4}
                                               multiline
                                               value={notes}
                                               onChange={handleNotesChange}
                                               disabled={!editable}
                                               sx={{
                                                   '.css-1sqnrkk-MuiInputBase-input-MuiOutlinedInput-input': {
                                                       color: 'black !important',
                                                   },

                                                   '.css-1sqnrkk-MuiInputBase-input-MuiOutlinedInput-input.Mui-disabled': {
                                                       webkitTextFillColor: 'black !important'
                                                   }
                                               }}
                                               InputProps={{
                                                   style: {
                                                       color: 'black',
                                                       fontFamily: 'Montserrat',
                                                       fontSize: 13,
                                                       '&.Mui-disabled': {
                                                           color: '#999999',
                                                           backgroundColor: 'red',
                                                       },
                                                       width: '380px'
                                                   }
                                               }}
                                               placeholder={'Add some notes...'}
                                    />
                                </Grid>
                                <Grid xs={12}>
                                    <Typography sx={{
                                        fontFamily: 'Montserrat',
                                        fontSize: 13,
                                        fontWeight: 'bold',
                                        mb: 1,
                                        color: '#334F68'
                                    }}>Client information</Typography>
                                    <TextField id="outlined-multiline-static"
                                               rows={4}
                                               multiline
                                               value={clientInformation}
                                               onChange={handleClientInfoChange}
                                               disabled={!editable}
                                               InputProps={{
                                                   style: {
                                                       color: 'black',
                                                       fontFamily: 'Montserrat',
                                                       fontSize: 13,
                                                       width: '380px'
                                                   }
                                               }}
                                               placeholder={'Client name\nclient@email.com\n+123456789'}
                                    />
                                </Grid>

                                <Grid item xs={12} container justifyContent='flex-end'>
                                    <Button onClick={handleEditClick}
                                            sx={{
                                                backgroundColor: '#FBFBFB',
                                                color: '#DC8045',
                                                fontFamily: 'Montserrat',
                                                fontWeight: 'bold',
                                                borderRadius: '5px',
                                                boxShadow: "0px 2px 5px rgba(0, 0, 0, 0.25)",
                                                ':hover': {
                                                    backgroundColor: '#FEFEFE'
                                                },
                                                ':focus, :active': {
                                                    outline: 'none'
                                                },
                                                height: 35,
                                                marginY: '18px',
                                                marginX: '6px'
                                            }}
                                    >{editable ? 'Cancel' : 'Edit'}</Button>

                                    {editable && (
                                        <Button onClick={handleSaveClick}
                                                sx={{
                                                    backgroundColor: '#FBFBFB',
                                                    color: '#DC8045',
                                                    fontFamily: 'Montserrat',
                                                    fontWeight: 'bold',
                                                    borderRadius: '5px',
                                                    boxShadow: "0px 2px 5px rgba(0, 0, 0, 0.25)",
                                                    ':hover': {
                                                        backgroundColor: '#FEFEFE'
                                                    },
                                                    ':focus, :active': {
                                                        outline: 'none'
                                                    },
                                                    height: 35,
                                                    marginLeft: '10px',
                                                    marginRight: '8px',
                                                    marginY: '18px'
                                                }}
                                        >
                                            Save
                                        </Button>
                                    )}
                                </Grid>
                            </Grid>
                        </Box>) : (
                        <Typography
                            style={{
                                fontFamily: 'Montserrat',
                                fontWeight: 'normal',
                                fontSize: '15px',
                                color: '#000000',
                                paddingLeft: '135px',
                                paddingTop: '250px',
                            }}
                        >
                            No projects available
                        </Typography>
                    )}
                </Box>
            </Box>
        </>
    );
}

export default ProjectDetails;