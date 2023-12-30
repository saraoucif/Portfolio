import React from 'react'
import MaterialTable from '@material-table/core';
import {useState} from 'react';
import axios from "axios";
import {useEffect} from "react";
import {TablePagination} from '@mui/material';
import {MTableToolbar} from "@material-table/core";
import SearchIcon from '@material-ui/icons/Search';
import ClearIcon from '@material-ui/icons/Clear';
import CheckIcon from '@mui/icons-material/Check';
import AddIcon from '@material-ui/icons/Add';
import CustomDatePicker from "./CustomDatePicker";
import EditIcon from '@mui/icons-material/Edit';
import DeleteIcon from '@mui/icons-material/Delete';
import './Table.css';
import '@material-ui/core/styles';

function Table(props) {
    const url = "http://35.222.169.45:8080/api/v1/project";
    const [data, setData] = useState([])
    const [selectedRow, setSelectedRow] = useState()
    const date = new Date();

    const columns = [
        {
            title: "Project", field: "projectName", width: "18%",
            validate: rowData => {
                if (rowData.projectName === undefined || rowData.projectName === "") {
                    return "Required"
                } else if (rowData.projectName.length < 3) {
                    return "Needs to be 3 characters or more"
                }
                return true
            }
        },

        {
            title: "Manager", field: "projectManager", width: "18%",
            validate: rowData => {
                if (rowData.projectManager === undefined || rowData.projectManager === "") {
                    return "Required"
                } else if (rowData.projectManager.length < 2) {
                    return "Needs to be 2 characters or more"
                }
                return true
            }
        },

        {
            title: "Status",
            field: "status",
            width: "14%",
            lookup: {"Not Started": "Not started", "Running": "Running", "Completed": "Completed"},
            initialEditValue: `Not Started`,
            validate: rowData => {
                if (rowData.status === undefined || rowData.status === "") {
                    return "Required"
                }
                return true
            }
        },

        {
            title: "Start Date", field: "startDate", type: "date", width: "18%", initialEditValue: Date.now(),
            dateSetting: {locale: "kr-KR"},
            filterComponent: (props) => <CustomDatePicker {...props} />,
            validate: rowData => {
                if (!rowData.startDate) {
                    return "Start date is required";
                }
                return true;
            }
        },

        {
            title: "Go Live Date",
            field: "goLiveDate",
            type: "date",
            width: "20%",
            initialEditValue: date.setMonth(date.getMonth() + 2),
            dateSetting: {locale: "kr-KR"},
            filterComponent: (props) => <CustomDatePicker {...props} />,
            validate: rowData => {
                if (rowData.goLiveDate === undefined || rowData.goLiveDate === "") {
                    return "Start date is required"
                }

                return true
            }
        },

        {
            title: "Team Size", field: "teamSize", type: "numeric", width: '18%', initialEditValue: 2,
            validate: rowData => {
                if (rowData.teamSize === undefined || rowData.teamSize === "") {
                    return "Required"
                } else if (rowData.teamSize < 2 || rowData.teamSize > 100) {
                    return "Invalid team size"
                }
                return true
            }
        },
    ]

    const fetchProjectData = () => {
        axios.get(url)
            .then((data) => {
                setData(data.data)
                if (data.data.length > 0) {
                    setSelectedRow(data.data[0]);
                    props.onSelection(data.data[0]);
                }
            })
            .catch(error => console.log(error))
    }

    useEffect(() => {
        fetchProjectData()
    }, [])

    useEffect(() => {
        if (props.updatedData) {
            const index = data.findIndex((item) => item.id === props.updatedData.id);
            data[index].milestone1 = props.updatedData.milestone1;
            data[index].milestone2 = props.updatedData.milestone2;
            data[index].milestone3 = props.updatedData.milestone3;
            data[index].milestone4 = props.updatedData.milestone4;
        }
    }, [props.updatedData])


    const onRowClick = (e, clickedRow) => {
        setSelectedRow(clickedRow);
        props.onSelection(clickedRow);
    };

    return (
        <div className="NewTable">
            <MaterialTable
                title=""
                data={data}
                columns={columns}
                onRowClick={onRowClick}
                icons={{
                    Add: () => <>
                        <div style={{
                            display: "flex",
                            alignItems: "center",
                            backgroundColor: "#ffffff",
                            width: 160,
                            height: 35,
                            boxShadow: "0px 2px 5px rgba(0, 0, 0, 0.25)",
                            borderRadius: "5px",
                            borderBottom: "1px solid #949494",
                        }}>
                            <span
                                style={{
                                    fontSize: 13,
                                    marginLeft: 0,
                                    fontFamily: "Montserrat",
                                    fontWeight: "bold",
                                    color: "#DC823D",
                                    textAlign: "center",
                                    padding: "15px",
                                }}
                            >
                              ADD PROJECT
                            </span>
                            <AddIcon style={{
                                color: "#DC823D",
                            }}/>
                        </div>
                    </>,
                    Search: () => <SearchIcon style={{color: "#DC823D"}}/>,
                    Clear: () => <ClearIcon style={{color: "#DC823D"}}/>,
                    Check: () => <CheckIcon style={{color: "#DC823D"}}/>,
                    Edit: () => <EditIcon style={{color: "#DC823D"}}/>,
                    Delete: () => <DeleteIcon style={{color: "#DC823D", height: 25, width: 25}}/>,
                }}

                localization={{
                    header: {
                        actions: ''
                    },
                    body: {
                        editTooltip: 'Edit project',
                        deleteTooltip: 'Delete project',
                        editRow: {
                            deleteText: 'Delete this project?',
                            deleteTextStyle: {
                                fontFamily: 'Montserrat',
                                fontSize: 20
                            }
                        },
                        addTooltip: 'Add project',
                        emptyDataSourceMessage:
                            <span
                                style={{
                                    fontFamily: 'Montserrat',
                                    fontWeight: 'normal',
                                    fontSize: '16px',
                                }}>
                              No projects available
                          </span>
                    },
                    pagination: {
                        labelRowsPerPage: "Rows per page",
                    },
                }
                }
                options={{
                    tableData: {
                        selectAll: true,
                    },
                    toolbar: true,
                    tableLayout: 'fixed',

                    headerStyle: {
                        border: '0.1px solid rgba(233, 235, 236, 0.5)',
                    },
                    rowStyle: (row) =>
                        row?.id === selectedRow?.id ? {backgroundColor: "#F4F4F4"} : {},

                    searchFieldAlignment: 'left',
                    searchFieldStyle: {
                        color: '#DC823D',
                        fontFamily: 'Montserrat',
                        paddingRight: 0,
                        boxShadow: "0px 2px 5px rgba(0, 0, 0, 0.25)",
                        borderRadius: "5px",
                        border: 100,
                        borderColor: 'red',
                        height: 35,
                        width: 350,
                        padding: '10px',
                    },
                    actionsColumnIndex: -1,
                    addRowPosition: "first",
                    headerSelectionProps: {
                        color: 'red'
                    },
                    pageSize: 10,
                    pageSizeOptions: [10, 20, 50],
                    labelRowsPerPage: 'Rows per page:'
                }}
                components={{
                    Toolbar: props => (
                        <div style={{
                            minHeight: '60px',
                            padding: '5px',
                            backgroundColor: 'white'
                        }}>
                            <MTableToolbar {...props} />
                        </div>
                    ),
                    Pagination: props => (
                        <TablePagination
                            {...props}
                            labelRowsPerPage={
                                <span style={{fontFamily: 'Montserrat', fontWeight: 'normal', color: '#334F68'}}>
                                    Rows per page:
                                </span>}
                            labelDisplayedRows={
                                ({from, to, count}) => (
                                    <span style={{
                                        fontFamily: 'Montserrat !important',
                                        fontWeight: 'bold',
                                        color: 'red !important'
                                    }}>
                                {from}-{to} of {count}
                                </span>
                                )}
                            rowsPerPageOptions={[10, 20, 50]}

                            SelectProps={{
                                style: {
                                    fontFamily: 'Montserrat',
                                    color: '#DC823D'
                                },
                                SelectDisplayProps: {
                                    style: {
                                        fontFamily: 'Montserrat'
                                    }
                                }
                            }}
                        />
                    ),
                }}

                editable={{
                    onRowAdd: (newRow) => new Promise((resolve, reject) => {
                        const startDateInMs = newRow.startDate;
                        const goLiveDateInMs = newRow.goLiveDate;
                        newRow.startDate = new Date(startDateInMs).toISOString().slice(0, 10);
                        newRow.goLiveDate = new Date(goLiveDateInMs).toISOString().slice(0, 10);

                        setTimeout(() => {
                            axios.post(url, newRow, {
                                headers: {
                                    "Content-Type": "application/json",
                                },
                            })
                            .then(function (response) {
                                newRow.id = response.data.id;
                                const updatedRows = [...data, newRow]
                                setData(updatedRows)
                            })
                            .catch(function (error) {
                                console.log(error);
                            });

                            resolve()
                        }, 1000)

                    }),
                    onRowDelete: (rowToDelete) => new Promise((resolve, reject) => {
                        const index = data.findIndex((item) => item.id === rowToDelete.id);
                        const updatedData = [...data]
                        updatedData.splice(index, 1)
                        const projectID = rowToDelete.id;

                        setTimeout(() => {
                            axios.delete(url + "/" + projectID, {
                                headers: {
                                    "Content-Type": "application/json",
                                },
                            })
                            .then(function (response) {
                            setData(updatedData);

                                if (data.length > 0 && selectedRow.id === rowToDelete.id) {
                                    setSelectedRow(data[0]);
                                    props.onSelection(data[0]);
                                }
                            })
                            .catch(function (error) {
                                console.log(error);
                            });
                            resolve()
                        }, 1000)

                    }),
                    onRowUpdate: (updatedRow, oldRow) => new Promise((resolve, reject) => {
                        const index = oldRow.tableData.index
                        const projectID = updatedRow.id;

                        if (updatedRow.startDate instanceof Date) {
                            const newStartDate = updatedRow.startDate.toISOString().slice(0, 10);
                            updatedRow.startDate = newStartDate;
                        }
                        if (updatedRow.goLiveDate instanceof Date) {
                            const newGoLiveDate = updatedRow.goLiveDate.toISOString().slice(0, 10);
                            updatedRow.goLiveDate = newGoLiveDate;
                        }

                        const updatedRows = [...data]
                        updatedRows[index] = updatedRow

                        setTimeout(() => {
                            axios.put(url + "/" + projectID, updatedRow, {
                                headers: {
                                    "Content-Type": "application/json",
                                },
                            }).then(function (response) {
                                setData(updatedRows)
                            })
                            .catch(function (error) {
                                console.log(error);
                            });

                            resolve()
                        }, 2000)
                    }),
                }}

            />
        </div>
    )
}

export default Table;