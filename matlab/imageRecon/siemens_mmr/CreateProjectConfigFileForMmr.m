%  *********************************************************************
%  Reconstruction Framework for Siemens Biograph mMR.  
%  Autor: Martín Belzunce. Kings College London.
%  Fecha de Creación: 15/04/2015
%  *********************************************************************
% Function that creates a config file to project an image with apirl.
% Optional parameter useGpu to use cuda projectors.

% Projection Parameters :=
% ; Archivo de configuración de reconstrucción MLEM para paper en Parallel Computing.
% input file := ../../../../images3D/point_source_all_FullFov_256_256_81.h33
% output type := Sinogram3D
% ; Projectors:
% projector := Siddon
% output projection := ../../inputData/sinograma3D_res5.00_zm0.00_192_248_41_span7.h33
% output filename := Project_PointSources_
% END :=

function CreateProjectConfigFileForMmr(configfilename, inputFile, outputSample, outputFilename, useGpu)

if nargin == 4
    useGpu = 0;
end

% Primero genero el archivo de encabezado.
fid = fopen(configfilename, 'w');
if(fid == -1)
    fprintf('No se pudo crear el archivo %s.', configfilename);
end
% Ahora debo ir escribiendo los campos. Algunos son fijos, y otros
% dependerán de la imagen:
fprintf(fid,'Projection Parameters :=\n');
fprintf(fid,'output type := Sinogram3DSiemensMmr\n');
if useGpu == 0
    fprintf(fid,'projector := Siddon\n');
else
    fprintf(fid,'projector := CuSiddonProjector\n');
    fprintf(fid,'projector block size := {256,1,1}\n');
    fprintf(fid,'gpu id := 0\n');
end
fprintf(fid,'input file := %s\n', inputFile);
fprintf(fid,'output projection := %s\n', outputSample);
fprintf(fid,'output filename := %s\n', outputFilename);

fclose(fid);
