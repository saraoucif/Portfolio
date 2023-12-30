package se.saga.kth.sagabackend.project;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@CrossOrigin(origins = "*", maxAge = 4800, allowCredentials = "false", allowedHeaders = "*", methods = {RequestMethod.GET, RequestMethod.POST, RequestMethod.PUT, RequestMethod.DELETE})
@RestController
@RequestMapping(path = "api/v1/project")
public class ProjectController{

    private final ProjectService projectService;

    @Autowired
    public ProjectController(ProjectService projectService) {
        this.projectService = projectService;
    }

    @GetMapping()
    public List<Project> getProjects(){
        return projectService.getProjects();
    }

    @GetMapping(path = "{projectID}")
    public Project getProject(@PathVariable("projectID")Integer projectID){
        return projectService.getProject(projectID);
    }

    @PostMapping
    public Project registerNewProject(@RequestBody Project project){
        Project savedProject = projectService.addNewProject(project);
        return savedProject;
    }

    @DeleteMapping(path = "{projectID}")
    public void deleteProject(@PathVariable("projectID")Integer projectID){
        projectService.deleteProject(projectID);
    }

    @PutMapping(path = "{projectID}")
    public void updateProject(@RequestBody Project project){
            projectService.updateProject(project);
    }

}
