Import("env")
import subprocess
import os

def linter_callback(*arg, **kwargs):
    print("Executing Flawfinder")
    # print(*args)
    # print(env.Dump())/
    # print(kwargs)
    #PROJECT_INCLUDE_DIR
    #PROJECT_SRC_DIR
    #__PIO_LIB_BUILDERS[0].path
    check_folders = [env.get("PROJECT_INCLUDE_DIR"), env.get("PROJECT_SRC_DIR")]
    for item in env.get("__PIO_LIB_BUILDERS"):
        check_folders.append(item.path)
    
    project_dir = env.get("PROJECT_DIR") + "\\"
    check_folders_without_prefix = [str(i).replace( project_dir, '') for i in check_folders]

    print("check folders", check_folders_without_prefix);
    
    flawfinder_arguments = env.GetProjectOption("flawfinder_arguments", "")

    subprocess.run("pip -q install flawfinder")
    files = []
    for folder in check_folders_without_prefix:
        # r=root, d=directories, f = files
        for r, d, f in os.walk(folder):
            for file in f:
                files.append(os.path.join(r, file))

    

    env.Execute("flawfinder  -C -c -D -i -S -Q " + " ".join(check_folders_without_prefix) + "  " + flawfinder_arguments)
    # env.Execute("lizard -Eduplicate "+ " ".join(check_folders_without_prefix))
    # for file in files:
    #     env.Execute("flawfinder "+ file)

env.AddCustomTarget(
    "flawfinder",
    None,
    linter_callback,
    title="flawfinder",
    description="Executes Flawfinder")
