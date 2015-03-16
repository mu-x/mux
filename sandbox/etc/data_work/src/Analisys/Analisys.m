function varargout = analisys(varargin)
% ANALISYS M-file for analisys.fig
%      ANALISYS, by itself, creates a new ANALISYS or raises the existing
%      singleton*.
%
%      H = ANALISYS returns the handle to a new ANALISYS or the handle to
%      the existing singleton*.
%
%      ANALISYS('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in ANALISYS.M with the given input arguments.
%
%      ANALISYS('Property','Value',...) creates a new ANALISYS or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before analisys_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to analisys_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help analisys

% Last Modified by GUIDE v2.5 19-Dec-2011 22:47:05

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @analisys_OpeningFcn, ...
                   'gui_OutputFcn',  @analisys_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before analisys is made visible.
function analisys_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to analisys (see VARARGIN)

% Choose default command line output for analisys
handles.output = hObject;

set(handles.uipanel6,'SelectionChangeFcn',@uipanel6_SelectionChangeFcn)

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes analisys wait for user response (see UIRESUME)
% uiwait(handles.figure1);
global A;
[filename, pathname] = uigetfile('*.dat', '����� �������� ������');
filepath = strcat(pathname, filename);
set(handles.filepath_obj,'String',filepath);
A = importdata(filepath,'\t',1);


% --- Outputs from this function are returned to the command line.
function varargout = analisys_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on selection change in listbox1.
function listbox1_Callback(hObject, eventdata, handles)
% hObject    handle to listbox1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns listbox1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from listbox1
int i;
global A;
i = get(hObject,'Value');

x = A.data(:,i);
Mx = mean(x);
Md = mode(x);
Me = median(x);
amin = min(x);
amax = max(x);
sko = std(x);
dis = var(x);

handles = guihandles(gcbo);
set(handles.edit1,'String',Mx);
set(handles.edit2,'String',dis);
set(handles.edit3,'String',amin);
set(handles.edit4,'String',amax);
set(handles.edit5,'String',sko);
set(handles.edit6,'String',Me);
set(handles.edit7,'String',Md);
a=get(handles.listbox1,'String');

temp = ['�����������(',a{i} , ')']
set(handles.text9,'String',temp);

hist(x);



% --- Executes during object creation, after setting all properties.
function listbox1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to listbox1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit1_Callback(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit1 as text
%        str2double(get(hObject,'String')) returns contents of edit1 as a double


% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit2_Callback(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit2 as text
%        str2double(get(hObject,'String')) returns contents of edit2 as a double


% --- Executes during object creation, after setting all properties.
function edit2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit3_Callback(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit3 as text
%        str2double(get(hObject,'String')) returns contents of edit3 as a double


% --- Executes during object creation, after setting all properties.
function edit3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit4_Callback(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit4 as text
%        str2double(get(hObject,'String')) returns contents of edit4 as a double


% --- Executes during object creation, after setting all properties.
function edit4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit5_Callback(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit5 as text
%        str2double(get(hObject,'String')) returns contents of edit5 as a double


% --- Executes during object creation, after setting all properties.
function edit5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit6_Callback(hObject, eventdata, handles)
% hObject    handle to edit6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit6 as text
%        str2double(get(hObject,'String')) returns contents of edit6 as a double


% --- Executes during object creation, after setting all properties.
function edit6_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit7_Callback(hObject, eventdata, handles)
% hObject    handle to edit7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit7 as text
%        str2double(get(hObject,'String')) returns contents of edit7 as a double


% --- Executes during object creation, after setting all properties.
function edit7_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in type_mdl.
function type_mdl_Callback(hObject, eventdata, handles)
% hObject    handle to type_mdl (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns type_mdl contents as cell array
%        contents{get(hObject,'Value')} returns selected item from type_mdl
tmp = get(hObject,'Value');
if (tmp == 1)
    handles = guihandles(gcbo);
    set(handles.pushbutton2,'Enable','off');
    set(handles.text12,'Enable','off');
    set(handles.edit9,'Enable','off');
    set(handles.text24,'Enable','off');
    set(handles.edit18,'Enable','off'); 
    set(handles.text11,'String','������������ ������:');
    set(handles.edit9,'String','');
    set(handles.edit10,'String',0);
    set(handles.edit8,'String','');
    set(handles.edit10,'String',0);
    set(handles.edit11,'String',0);
    set(handles.edit12,'String',0);
    set(handles.edit13,'String',0);
    set(handles.edit14,'String',0);
    set(handles.edit15,'String',0);
    set(handles.edit16,'String',0);
    set(handles.edit17,'String',0);
    
    set(handles.edit19,'String',0);
    set(handles.edit20,'String',0);
    set(handles.edit21,'String',0);
    set(handles.edit22,'String',0);
    set(handles.edit23,'String',0);    
    set(handles.edit24,'String',0);
    set(handles.edit25,'String',0);  
    set(handles.edit26,'String',0);
    set(handles.edit27,'String',0);
    set(handles.edit28,'String',0);
    set(handles.edit29,'String',0);
    set(handles.edit30,'String',0);
    set(handles.edit31,'String',0);
    set(handles.edit32,'String',0);
else
    set(handles.pushbutton2,'Enable','off');
    set(handles.edit8,'String','a1+a2*exp(x1)+a3*x2*x2');
    set(handles.edit10,'String',0);
    set(handles.edit11,'String',0);
    set(handles.edit12,'String',0);
    set(handles.edit13,'String',0);
    set(handles.edit14,'String',0);
    set(handles.edit15,'String',0);
    set(handles.edit16,'String',0);
    set(handles.edit17,'String',0);
    set(handles.text11,'String','������� ������:        ');
    set(handles.text12,'Enable','on');
    set(handles.edit9,'Enable','on');  
    set(handles.text24,'Enable','on');
    set(handles.edit18,'Enable','on'); 
    
    set(handles.edit19,'String',0);
    set(handles.edit20,'String',0);
    set(handles.edit21,'String',0);
    set(handles.edit22,'String',0);
    set(handles.edit23,'String',0);    
    set(handles.edit24,'String',0);
    set(handles.edit25,'String',0);  
    set(handles.edit26,'String',0);
    set(handles.edit27,'String',0);
    set(handles.edit28,'String',0);
    set(handles.edit29,'String',0);
    set(handles.edit30,'String',0);
    set(handles.edit31,'String',0);
    set(handles.edit32,'String',0);
end


% --- Executes during object creation, after setting all properties.
function type_mdl_CreateFcn(hObject, eventdata, handles)
% hObject    handle to type_mdl (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
    global A;
    global k2;
    global r;
    global y;
    
    i = 1;
    handles = guihandles(gcbo);
    
    if (get(handles.checkbox2,'Value') == 1)
        k(i) = 1;
        i = i+1;
    end
    if (get(handles.checkbox3,'Value') == 1)
        k(i) = 2;
        i = i+1;
    end
    if (get(handles.checkbox4,'Value') == 1)
        k(i) = 3;
        i = i+1;
    end
    if (get(handles.checkbox5,'Value') == 1)
        k(i) = 4;
        i = i+1;
    end
    if (get(handles.checkbox6,'Value') == 1)
        k(i) = 5;
        i = i+1;
    end
    if (get(handles.checkbox7,'Value') == 1)
        k(i) = 6;
        i = i+1;
    end
    if (get(handles.checkbox8,'Value') == 1)
        k(i) = 7;
        i = i+1;
    end
    if (get(handles.checkbox9,'Value') == 1)
        k(i) = 8;
        i = i+1;
    end
    if (get(handles.checkbox10,'Value') == 1)
        k(i) = 9;
        i = i+1;
    end
    if (get(handles.checkbox11,'Value') == 1)
        k(i) = 10;
        i = i+1;
    end
    if (get(handles.checkbox12,'Value') == 1)
        k(i) = 11;
        i = i+1;
    end
    if (get(handles.checkbox13,'Value') == 1)
        k(i) = 12;
        i = i+1;
    end
    
if (get(handles.type_mdl,'Value') == 1)
    
    if exist('k') == 1
    x = A.data(:,k);
    y = A.data(:,k2);
    cols = A.textdata(:)';
    cols2 = char(cols); 
    szx = size(x(1,:)',1);
    if szx==1 
        mdl = @(a,x)(a(1) + a(2)*x(:,1));
        mdl_str = sprintf('%s = %%f+%%f*%s', cols2(k2,:), cols2(k(1),:));
    end;
    if szx==2 
        mdl = @(a,x)(a(1) + a(2)*x(:,1) + a(3)*x(:,2));
        mdl_str = sprintf('%s = %%f+%%f*%s+%%f*%s', cols2(k2,:), cols2(k(1),:), cols2(k(2),:));
    end;
    if szx==3 
        mdl = @(a,x)(a(1) + a(2).*x(:,1) + a(3).*x(:,2) + a(4).*x(:,3));
        mdl_str = sprintf('%s = %%f+%%f*%s+%%f*%s+%%f*%s', cols2(k2,:), cols2(k(1),:), cols2(k(2),:), cols2(k(3),:));
    end;
    if szx==4 
        mdl = @(a,x)(a(1) + a(2)*x(:,1) + a(3)*x(:,2) + a(4)*x(:,3) + a(5)*x(:,4));
        mdl_str = sprintf('%s = %%f+%%f*%s+%%f*%s+%%f*%s+%%f*%s', cols2(k2,:), cols2(k(1),:), cols2(k(2),:), cols2(k(3),:), cols2(k(4),:));
    end;
    if szx==5 
        mdl = @(a,x)(a(1) + a(2)*x(:,1) + a(3)*x(:,2) + a(4)*x(:,3) + a(5)*x(:,4) + a(6)*x(:,5));
        mdl_str = sprintf('%s = %%f+%%f*%s+%%f*%s+%%f*%s+%%f*%s+%%f*%s', cols2(k2,:), cols2(k(1),:), cols2(k(2),:), cols2(k(3),:), cols2(k(4),:), cols2(k(5),:));
    end;
    if szx==6 
        mdl = @(a,x)(a(1) + a(2)*x(:,1) + a(3)*x(:,2) + a(4)*x(:,3) + a(5)*x(:,4) + a(6)*x(:,5) + a(7)*x(:,6));
        mdl_str = sprintf('%s = %%f+%%f*%s+%%f*%s+%%f*%s+%%f*%s+%%f*%s+%%f*%s', cols2(k2,:), cols2(k(1),:), cols2(k(2),:), cols2(k(3),:), cols2(k(4),:), cols2(k(5),:), cols2(k(6),:));
    end;
    if szx==7 
        mdl = @(a,x)(a(1) + a(2)*x(:,1) + a(3)*x(:,2) + a(4)*x(:,3) + a(5)*x(:,4) + a(6)*x(:,5) + a(7)*x(:,6) + a(8)*x(:,7));
        mdl_str = sprintf('%s = %%f+%%f*%s+%%f*%s+%%f*%s+%%f*%s+%%f*%s+%%f*%s+%%f*%s', cols2(k2,:), cols2(k(1),:), cols2(k(2),:), cols2(k(3),:), cols2(k(4),:), cols2(k(5),:), cols2(k(6),:), cols2(k(7),:));
    end;
    if szx==8 
        mdl = @(a,x)(a(1) + a(2)*x(:,1) + a(3)*x(:,2) + a(4)*x(:,3) + a(5)*x(:,4) + a(6)*x(:,5) + a(7)*x(:,6) + a(8)*x(:,7) + a(9)*x(:,8));
        mdl_str = sprintf('%s = %%f+%%f*%s+%%f*%s+%%f*%s+%%f*%s+%%f*%s+%%f*%s+%%f*%s+%%f*%s', cols2(k2,:), cols2(k(1),:), cols2(k(2),:), cols2(k(3),:), cols2(k(4),:), cols2(k(5),:), cols2(k(6),:), cols2(k(7),:), cols2(k(8),:));
    end;
    
    szx2 = szx;
    if exist('szx2') == 1
    a = ones(1+szx2,1);
    a0 = [5;2*ones(szx2,1)];
    try
        [ahat,r,J,cov,msee] = nlinfit(x,y,mdl,a0);
    catch
        msgbox('������ ��� ���������� �������� ������!');
    end
    
    ci = nlparci(ahat,r,'Jacobian',J);
    
    set(handles.pushbutton2,'Enable','on');
    set(handles.edit10,'String',msee);
    l = sprintf(mdl_str, ahat);
    fin_str = sprintf(mdl_str, ahat);
    fin_str = strrep(fin_str,'  +-','-');
    fin_str = strrep(fin_str,'+-','-');
    fin_str = strrep(fin_str,' +-','-');
    set(handles.edit8,'String',fin_str);
    end;

    if (size(k,2) == 1)
        set(handles.edit11,'String',ahat(1));
        set(handles.edit12,'String',ahat(2));
        set(handles.edit13,'String',0);
        set(handles.edit14,'String',0);
        set(handles.edit15,'String',0);
        set(handles.edit16,'String',0);
        set(handles.edit17,'String',0);
        
        set(handles.edit19,'String',ci(1,2));
        set(handles.edit20,'String',ci(1,1));
        set(handles.edit21,'String',ci(2,2));
        set(handles.edit22,'String',ci(2,1));
        set(handles.edit23,'String',0);
        set(handles.edit24,'String',0);
        set(handles.edit25,'String',0);  
        set(handles.edit26,'String',0);
        set(handles.edit27,'String',0);
        set(handles.edit28,'String',0);
        set(handles.edit29,'String',0);
        set(handles.edit30,'String',0);
        set(handles.edit31,'String',0);
        set(handles.edit32,'String',0);
    end;
    if (size(k,2) == 2)
        set(handles.edit11,'String',ahat(1));
        set(handles.edit12,'String',ahat(2));
        set(handles.edit13,'String',ahat(3));
        set(handles.edit14,'String',0);
        set(handles.edit15,'String',0);
        set(handles.edit16,'String',0);
        set(handles.edit17,'String',0);
        
        set(handles.edit19,'String',ci(1,2));
        set(handles.edit20,'String',ci(1,1));
        set(handles.edit21,'String',ci(2,2));
        set(handles.edit22,'String',ci(2,1));
        set(handles.edit23,'String',ci(3,2));
        set(handles.edit24,'String',ci(3,1));
        set(handles.edit25,'String',0);  
        set(handles.edit26,'String',0);
        set(handles.edit27,'String',0);
        set(handles.edit28,'String',0);
        set(handles.edit29,'String',0);
        set(handles.edit30,'String',0);
        set(handles.edit31,'String',0);
        set(handles.edit32,'String',0);
    end
    if (size(k,2) == 3)
        set(handles.edit11,'String',ahat(1));
        set(handles.edit12,'String',ahat(2));
        set(handles.edit13,'String',ahat(3));
        set(handles.edit14,'String',ahat(4));
        set(handles.edit15,'String',0);
        set(handles.edit16,'String',0);
        set(handles.edit17,'String',0);
        
        set(handles.edit19,'String',ci(1,2));
        set(handles.edit20,'String',ci(1,1));
        set(handles.edit21,'String',ci(2,2));
        set(handles.edit22,'String',ci(2,1));
        set(handles.edit23,'String',ci(3,2));
        set(handles.edit24,'String',ci(3,1));
        set(handles.edit25,'String',ci(4,2));  
        set(handles.edit26,'String',ci(4,1));
        set(handles.edit27,'String',0);
        set(handles.edit28,'String',0);
        set(handles.edit29,'String',0);
        set(handles.edit30,'String',0);
        set(handles.edit31,'String',0);
        set(handles.edit32,'String',0);
    end;
    if (size(k,2) == 4)
        set(handles.edit11,'String',ahat(1));
        set(handles.edit12,'String',ahat(2));
        set(handles.edit13,'String',ahat(3));
        set(handles.edit14,'String',ahat(4));
        set(handles.edit15,'String',ahat(5));
        set(handles.edit16,'String',0);
        set(handles.edit17,'String',0);
        
        set(handles.edit19,'String',ci(1,2));
        set(handles.edit20,'String',ci(1,1));
        set(handles.edit21,'String',ci(2,2));
        set(handles.edit22,'String',ci(2,1));
        set(handles.edit23,'String',ci(3,2));
        set(handles.edit24,'String',ci(3,1));
        set(handles.edit25,'String',ci(4,2));  
        set(handles.edit26,'String',ci(4,1));
        set(handles.edit27,'String',ci(5,2));
        set(handles.edit28,'String',ci(5,1));
        set(handles.edit29,'String',0);
        set(handles.edit30,'String',0);
        set(handles.edit31,'String',0);
        set(handles.edit32,'String',0);
    end;
    if (size(k,2) == 5)
        set(handles.edit11,'String',ahat(1));
        set(handles.edit12,'String',ahat(2));
        set(handles.edit13,'String',ahat(3));
        set(handles.edit14,'String',ahat(4));
        set(handles.edit15,'String',ahat(5));
        set(handles.edit16,'String',ahat(6));
        set(handles.edit17,'String',0);
        
        set(handles.edit19,'String',ci(1,2));
        set(handles.edit20,'String',ci(1,1));
        set(handles.edit21,'String',ci(2,2));
        set(handles.edit22,'String',ci(2,1));
        set(handles.edit23,'String',ci(3,2));
        set(handles.edit24,'String',ci(3,1));
        set(handles.edit25,'String',ci(4,2));  
        set(handles.edit26,'String',ci(4,1));
        set(handles.edit27,'String',ci(5,2));
        set(handles.edit28,'String',ci(5,1));
        set(handles.edit29,'String',ci(6,2));
        set(handles.edit30,'String',ci(6,1));
        set(handles.edit31,'String',0);
        set(handles.edit32,'String',0);
    end
    if (size(k,2) == 6)
        set(handles.edit11,'String',ahat(1));
        set(handles.edit12,'String',ahat(2));
        set(handles.edit13,'String',ahat(3));
        set(handles.edit14,'String',ahat(4));
        set(handles.edit15,'String',ahat(5));
        set(handles.edit16,'String',ahat(6));
        set(handles.edit17,'String',ahat(7));
        
        set(handles.edit19,'String',ci(1,2));
        set(handles.edit20,'String',ci(1,1));
        set(handles.edit21,'String',ci(2,2));
        set(handles.edit22,'String',ci(2,1));
        set(handles.edit23,'String',ci(3,2));
        set(handles.edit24,'String',ci(3,1));
        set(handles.edit25,'String',ci(4,2));  
        set(handles.edit26,'String',ci(4,1));
        set(handles.edit27,'String',ci(5,2));
        set(handles.edit28,'String',ci(5,1));
        set(handles.edit29,'String',ci(6,2));
        set(handles.edit30,'String',ci(6,1));
        set(handles.edit31,'String',ci(7,1));
        set(handles.edit32,'String',ci(7,2));
    end
    
    else
        msgbox('�� ���������� ������� ��������!');
    end;
else
    if exist('k') == 1
    A.data =  sortrows(A.data,k2);
    x = A.data(:,k);
    y = A.data(:,k2);
    modl = get(handles.edit8,'String');
    set(handles.pushbutton2,'Enable','on');
    old_modl = modl;
    max_a = str2num(get(handles.edit18,'String'));
    modl = regexprep(modl,'x([0-9]*)\*x','x$1\.\*x')
    for i=max_a:-1:1
        modl = regexprep(modl,['a',num2str(i)],['a(',num2str(i),')']);
        modl = regexprep(modl,['x',num2str(i)],['x(:,',num2str(i),')']);
    end
    mdl = @(a,x)(eval(modl));
    a0 = 2*ones(max_a,1);
    try
        [ahat,r,J,cov,mseee] = nlinfit(x,y,mdl,a0);
    catch
        msgbox('������ ��� ���������� ���������� ������!');
    end
        
    ci = nlparci(ahat,r,'Jacobian',J);
    
    set(handles.edit10,'String',mseee);   
    if (size(k,2) == 1)
        set(handles.edit11,'String',ahat(1));
        set(handles.edit12,'String',ahat(2));
        set(handles.edit13,'String',0);
        set(handles.edit14,'String',0);
        set(handles.edit15,'String',0);
        set(handles.edit16,'String',0);
        set(handles.edit17,'String',0);
        
        set(handles.edit19,'String',ci(1,2));
        set(handles.edit20,'String',ci(1,1));
        set(handles.edit21,'String',ci(2,2));
        set(handles.edit22,'String',ci(2,1));
        set(handles.edit23,'String',0);
        set(handles.edit24,'String',0);
        set(handles.edit25,'String',0);  
        set(handles.edit26,'String',0);
        set(handles.edit27,'String',0);
        set(handles.edit28,'String',0);
        set(handles.edit29,'String',0);
        set(handles.edit30,'String',0);
        set(handles.edit31,'String',0);
        set(handles.edit32,'String',0);
    end;
    if (size(k,2) == 2)
        set(handles.edit11,'String',ahat(1));
        set(handles.edit12,'String',ahat(2));
        set(handles.edit13,'String',ahat(3));
        set(handles.edit14,'String',0);
        set(handles.edit15,'String',0);
        set(handles.edit16,'String',0);
        set(handles.edit17,'String',0);
        
        set(handles.edit19,'String',ci(1,2));
        set(handles.edit20,'String',ci(1,1));
        set(handles.edit21,'String',ci(2,2));
        set(handles.edit22,'String',ci(2,1));
        set(handles.edit23,'String',ci(3,2));
        set(handles.edit24,'String',ci(3,1));
        set(handles.edit25,'String',0);  
        set(handles.edit26,'String',0);
        set(handles.edit27,'String',0);
        set(handles.edit28,'String',0);
        set(handles.edit29,'String',0);
        set(handles.edit30,'String',0);
        set(handles.edit31,'String',0);
        set(handles.edit32,'String',0);
    end
    if (size(k,2) == 3)
        set(handles.edit11,'String',ahat(1));
        set(handles.edit12,'String',ahat(2));
        set(handles.edit13,'String',ahat(3));
        set(handles.edit14,'String',ahat(4));
        set(handles.edit15,'String',0);
        set(handles.edit16,'String',0);
        set(handles.edit17,'String',0);
        
        set(handles.edit19,'String',ci(1,2));
        set(handles.edit20,'String',ci(1,1));
        set(handles.edit21,'String',ci(2,2));
        set(handles.edit22,'String',ci(2,1));
        set(handles.edit23,'String',ci(3,2));
        set(handles.edit24,'String',ci(3,1));
        set(handles.edit25,'String',ci(4,2));  
        set(handles.edit26,'String',ci(4,1));
        set(handles.edit27,'String',0);
        set(handles.edit28,'String',0);
        set(handles.edit29,'String',0);
        set(handles.edit30,'String',0);
        set(handles.edit31,'String',0);
        set(handles.edit32,'String',0);
    end;
    if (size(k,2) == 4)
        set(handles.edit11,'String',ahat(1));
        set(handles.edit12,'String',ahat(2));
        set(handles.edit13,'String',ahat(3));
        set(handles.edit14,'String',ahat(4));
        set(handles.edit15,'String',ahat(5));
        set(handles.edit16,'String',0);
        set(handles.edit17,'String',0);
        
        set(handles.edit19,'String',ci(1,2));
        set(handles.edit20,'String',ci(1,1));
        set(handles.edit21,'String',ci(2,2));
        set(handles.edit22,'String',ci(2,1));
        set(handles.edit23,'String',ci(3,2));
        set(handles.edit24,'String',ci(3,1));
        set(handles.edit25,'String',ci(4,2));  
        set(handles.edit26,'String',ci(4,1));
        set(handles.edit27,'String',ci(5,2));
        set(handles.edit28,'String',ci(5,1));
        set(handles.edit29,'String',0);
        set(handles.edit30,'String',0);
        set(handles.edit31,'String',0);
        set(handles.edit32,'String',0);
    end;
    if (size(k,2) == 5)
        set(handles.edit11,'String',ahat(1));
        set(handles.edit12,'String',ahat(2));
        set(handles.edit13,'String',ahat(3));
        set(handles.edit14,'String',ahat(4));
        set(handles.edit15,'String',ahat(5));
        set(handles.edit16,'String',ahat(6));
        set(handles.edit17,'String',0);
        
        set(handles.edit19,'String',ci(1,2));
        set(handles.edit20,'String',ci(1,1));
        set(handles.edit21,'String',ci(2,2));
        set(handles.edit22,'String',ci(2,1));
        set(handles.edit23,'String',ci(3,2));
        set(handles.edit24,'String',ci(3,1));
        set(handles.edit25,'String',ci(4,2));  
        set(handles.edit26,'String',ci(4,1));
        set(handles.edit27,'String',ci(5,2));
        set(handles.edit28,'String',ci(5,1));
        set(handles.edit29,'String',ci(6,2));
        set(handles.edit30,'String',ci(6,1));
        set(handles.edit31,'String',0);
        set(handles.edit32,'String',0);
    end
    if (size(k,2) == 6)
        set(handles.edit11,'String',ahat(1));
        set(handles.edit12,'String',ahat(2));
        set(handles.edit13,'String',ahat(3));
        set(handles.edit14,'String',ahat(4));
        set(handles.edit15,'String',ahat(5));
        set(handles.edit16,'String',ahat(6));
        set(handles.edit17,'String',ahat(7));
        
        set(handles.edit19,'String',ci(1,2));
        set(handles.edit20,'String',ci(1,1));
        set(handles.edit21,'String',ci(2,2));
        set(handles.edit22,'String',ci(2,1));
        set(handles.edit23,'String',ci(3,2));
        set(handles.edit24,'String',ci(3,1));
        set(handles.edit25,'String',ci(4,2));  
        set(handles.edit26,'String',ci(4,1));
        set(handles.edit27,'String',ci(5,2));
        set(handles.edit28,'String',ci(5,1));
        set(handles.edit29,'String',ci(6,2));
        set(handles.edit30,'String',ci(6,1));
        set(handles.edit31,'String',ci(7,1));
        set(handles.edit32,'String',ci(7,2));
    end
    
    for i=max_a:-1:1
        old_modl = regexprep(old_modl,['a',num2str(i)],num2str(ahat(i)));
    end
    old_modl = strrep(old_modl,'+-','-');
    
    set(handles.edit9,'String',old_modl);
    else
        msgbox('�� ���������� ������� ��������!');
    end
end;


% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
handles = guihandles(gcbo);

global r;
global y;
h1=figure;
tmp = get(handles.type_mdl,'Value');
if (tmp == 1)
    a1=scatter(r,y-r,5,[1 0 0]);
    title('������������� �������� ���������');
    legend('������� �� �������������');
else
    a1=scatter(r,y-r,5,[1 0 0]);
    title('������������� ���������� ���������');
    legend('������� �� �������������');
end



% --- Executes on button press in pushbutton3.
function pushbutton3_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
close(handles.figure1);


function edit8_Callback(hObject, eventdata, handles)
% hObject    handle to edit8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit8 as text
%        str2double(get(hObject,'String')) returns contents of edit8 as a double


% --- Executes during object creation, after setting all properties.
function edit8_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit9_Callback(hObject, eventdata, handles)
% hObject    handle to edit9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit9 as text
%        str2double(get(hObject,'String')) returns contents of edit9 as a double


% --- Executes during object creation, after setting all properties.
function edit9_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in checkbox2.
function checkbox2_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox2


% --- Executes on button press in checkbox3.
function checkbox3_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox3


% --- Executes on button press in checkbox4.
function checkbox4_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox4


% --- Executes on button press in checkbox5.
function checkbox5_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox5


% --- Executes on button press in checkbox6.
function checkbox6_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox6


% --- Executes on button press in checkbox7.
function checkbox7_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox7


% --- Executes on button press in checkbox8.
function checkbox8_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox8


% --- Executes on button press in checkbox9.
function checkbox9_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox9


% --- Executes on button press in checkbox10.
function checkbox10_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox10 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox10


% --- Executes on button press in checkbox11.
function checkbox11_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox11


% --- Executes on button press in checkbox12.
function checkbox12_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox12


% --- Executes on button press in checkbox13.
function checkbox13_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox13 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox13


% --- If Enable == 'on', executes on mouse press in 5 pixel border.
% --- Otherwise, executes on mouse press in 5 pixel border or over pushbutton3.
function pushbutton3_ButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



function edit10_Callback(hObject, eventdata, handles)
% hObject    handle to edit10 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit10 as text
%        str2double(get(hObject,'String')) returns contents of edit10 as a double


% --- Executes during object creation, after setting all properties.
function edit10_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit10 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit11_Callback(hObject, eventdata, handles)
% hObject    handle to edit11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit11 as text
%        str2double(get(hObject,'String')) returns contents of edit11 as a double


% --- Executes during object creation, after setting all properties.
function edit11_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit12_Callback(hObject, eventdata, handles)
% hObject    handle to edit12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit12 as text
%        str2double(get(hObject,'String')) returns contents of edit12 as a double


% --- Executes during object creation, after setting all properties.
function edit12_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit13_Callback(hObject, eventdata, handles)
% hObject    handle to edit13 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit13 as text
%        str2double(get(hObject,'String')) returns contents of edit13 as a double


% --- Executes during object creation, after setting all properties.
function edit13_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit13 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit14_Callback(hObject, eventdata, handles)
% hObject    handle to edit14 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit14 as text
%        str2double(get(hObject,'String')) returns contents of edit14 as a double


% --- Executes during object creation, after setting all properties.
function edit14_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit14 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit15_Callback(hObject, eventdata, handles)
% hObject    handle to edit15 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit15 as text
%        str2double(get(hObject,'String')) returns contents of edit15 as a double


% --- Executes during object creation, after setting all properties.
function edit15_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit15 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit16_Callback(hObject, eventdata, handles)
% hObject    handle to edit16 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit16 as text
%        str2double(get(hObject,'String')) returns contents of edit16 as a double


% --- Executes during object creation, after setting all properties.
function edit16_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit16 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit17_Callback(hObject, eventdata, handles)
% hObject    handle to edit17 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit17 as text
%        str2double(get(hObject,'String')) returns contents of edit17 as a double


% --- Executes during object creation, after setting all properties.
function edit17_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit17 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function uipanel6_SelectionChangeFcn(hObject, eventdata)

%retrieve GUI data, i.e. the handles structure
handles = guidata(hObject); 
global k2;

switch get(eventdata.NewValue,'Tag')   % Get Tag of selected object
    case 'radiobutton4'
        k2 = 1;
    case 'radiobutton5'
        k2 = 2;
    case 'radiobutton6'
        k2 = 3;
    case 'radiobutton7'
        k2 = 4;
    case 'radiobutton8'
        k2 = 5;
    case 'radiobutton9'
        k2 = 6;
    case 'radiobutton10'
        k2 = 7;
    case 'radiobutton11'
        k2 = 8;
    case 'radiobutton16'
        k2 = 9;
    case 'radiobutton17'
        k2 = 10;
    case 'radiobutton18'
        k2 = 11;
    case 'radiobutton19'
        k2 = 12;
    otherwise
        k2 = 12;

end
%updates the handles structure
guidata(hObject, handles);



function edit18_Callback(hObject, eventdata, handles)
% hObject    handle to edit18 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit18 as text
%        str2double(get(hObject,'String')) returns contents of edit18 as a double


% --- Executes during object creation, after setting all properties.
function edit18_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit18 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit19_Callback(hObject, eventdata, handles)
% hObject    handle to edit19 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit19 as text
%        str2double(get(hObject,'String')) returns contents of edit19 as a double


% --- Executes during object creation, after setting all properties.
function edit19_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit19 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit20_Callback(hObject, eventdata, handles)
% hObject    handle to edit20 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit20 as text
%        str2double(get(hObject,'String')) returns contents of edit20 as a double


% --- Executes during object creation, after setting all properties.
function edit20_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit20 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit21_Callback(hObject, eventdata, handles)
% hObject    handle to edit21 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit21 as text
%        str2double(get(hObject,'String')) returns contents of edit21 as a double


% --- Executes during object creation, after setting all properties.
function edit21_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit21 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit22_Callback(hObject, eventdata, handles)
% hObject    handle to edit22 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit22 as text
%        str2double(get(hObject,'String')) returns contents of edit22 as a double


% --- Executes during object creation, after setting all properties.
function edit22_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit22 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit23_Callback(hObject, eventdata, handles)
% hObject    handle to edit23 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit23 as text
%        str2double(get(hObject,'String')) returns contents of edit23 as a double


% --- Executes during object creation, after setting all properties.
function edit23_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit23 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit24_Callback(hObject, eventdata, handles)
% hObject    handle to edit24 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit24 as text
%        str2double(get(hObject,'String')) returns contents of edit24 as a double


% --- Executes during object creation, after setting all properties.
function edit24_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit24 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit25_Callback(hObject, eventdata, handles)
% hObject    handle to edit25 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit25 as text
%        str2double(get(hObject,'String')) returns contents of edit25 as a double


% --- Executes during object creation, after setting all properties.
function edit25_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit25 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit26_Callback(hObject, eventdata, handles)
% hObject    handle to edit26 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit26 as text
%        str2double(get(hObject,'String')) returns contents of edit26 as a double


% --- Executes during object creation, after setting all properties.
function edit26_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit26 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit27_Callback(hObject, eventdata, handles)
% hObject    handle to edit27 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit27 as text
%        str2double(get(hObject,'String')) returns contents of edit27 as a double


% --- Executes during object creation, after setting all properties.
function edit27_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit27 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit28_Callback(hObject, eventdata, handles)
% hObject    handle to edit28 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit28 as text
%        str2double(get(hObject,'String')) returns contents of edit28 as a double


% --- Executes during object creation, after setting all properties.
function edit28_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit28 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit29_Callback(hObject, eventdata, handles)
% hObject    handle to edit29 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit29 as text
%        str2double(get(hObject,'String')) returns contents of edit29 as a double


% --- Executes during object creation, after setting all properties.
function edit29_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit29 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit30_Callback(hObject, eventdata, handles)
% hObject    handle to edit30 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit30 as text
%        str2double(get(hObject,'String')) returns contents of edit30 as a double


% --- Executes during object creation, after setting all properties.
function edit30_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit30 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit31_Callback(hObject, eventdata, handles)
% hObject    handle to edit31 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit31 as text
%        str2double(get(hObject,'String')) returns contents of edit31 as a double


% --- Executes during object creation, after setting all properties.
function edit31_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit31 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit32_Callback(hObject, eventdata, handles)
% hObject    handle to edit32 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit32 as text
%        str2double(get(hObject,'String')) returns contents of edit32 as a double


% --- Executes during object creation, after setting all properties.
function edit32_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit32 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function filepath_obj_Callback(hObject, eventdata, handles)
% hObject    handle to filepath_obj (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of filepath_obj as text
%        str2double(get(hObject,'String')) returns contents of filepath_obj as a double
global A;
[filename, pathname] = uigetfile('*.dat', '����� �������� ������');
filepath = strcat(pathname, filename);
set(hObject,'String',filepath);
A = importdata(filepath,'\t',1);

% --- Executes during object creation, after setting all properties.
function filepath_obj_CreateFcn(hObject, eventdata, handles)
% hObject    handle to filepath_obj (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on key press with focus on filepath_obj and none of its controls.
function filepath_obj_KeyPressFcn(hObject, eventdata, handles)
% hObject    handle to filepath_obj (see GCBO)
% eventdata  structure with the following fields (see UICONTROL)
%	Key: name of the key that was pressed, in lower case
%	Character: character interpretation of the key(s) that was pressed
%	Modifier: name(s) of the modifier key(s) (i.e., control, shift) pressed
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton4.
function pushbutton4_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function figure1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
