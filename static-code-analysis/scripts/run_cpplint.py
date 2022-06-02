Import("env")
import subprocess
import os

def linter_callback(*arg, **kwargs):
    print("Executing Linter")
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
    
    # cyclomatic_complexity_analyzer = env.GetProjectOption("cyclomatic_complexity_analyzer", "")

    subprocess.run("pip -q install cpplint")
    files = []
    for folder in check_folders_without_prefix:
        # r=root, d=directories, f = files
        for r, d, f in os.walk(folder):
            for file in f:
                files.append(os.path.join(r, file))

    # env.Execute("lizard " + " ".join(check_folders_without_prefix) + "  " + cyclomatic_complexity_analyzer)
    # env.Execute("lizard -Eduplicate "+ " ".join(check_folders_without_prefix))
    for file in files:
        env.Execute("cpplint "+ file)

env.AddCustomTarget(
    "lint",
    None,
    linter_callback,
    title="lint",
    description="Executes Linter")
