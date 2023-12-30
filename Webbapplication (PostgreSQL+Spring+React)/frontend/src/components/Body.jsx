import React, {useState} from 'react';
import ProjectDetails from "./ProjectDetails";
import Table from "./Table.jsx";
import './Body.css';

function Body() {

    const [selectedData, setSelectedData] = useState(null);
    const [updatedData, setUpdatedData] = useState(null);

    const handleDataSelection = (data) => {
        setSelectedData(data);
    };

    const handleDataUpdate = (updatedData) => {
        setUpdatedData(updatedData);
    };

    return (
        <div style={{
            display: 'flex',
            alignItems: 'stretch',
            justifyContent: 'center',
            backgroundColor: '#E9EBEC',
            width: '100%',
            height: '100vh',
            overflowX: 'hidden',
            boxSizing: 'border-box',
            paddingLeft: '2.2rem',
            paddingRight: '2.2rem',
        }}>
            <div style={{flex: 5}}>
                <Table
                    onSelection={handleDataSelection}
                    updatedData={updatedData}
                />
            </div>
            <div style={{flex: 2, marginLeft: '1.5rem'}}>
                <ProjectDetails
                    onDataUpdate={handleDataUpdate}
                    selectedData={selectedData}
                />
            </div>
        </div>
    );
}

export default Body;